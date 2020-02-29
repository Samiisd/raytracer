//
// Created by ultra on 2/20/20.
//

#include "renderer.h"

Image Renderer::render(const size_t depth) const {
  Image result(imHeight, imWidth);

  const Camera &camera = scene.camera;

  // Iterate over all pixels of the image
  for (size_t y = 0; y < imHeight; y++) {
    for (size_t x = 0; x < imWidth; x++) {
      Ray r = {camera.eye(),
               (camera.pixelToWorld(y, x) - camera.eye()).normalized()};

      result(y, x) = castRay(r, depth);
    }
  }

  return result;
}

Vec3 Renderer::castRay(const Ray &ray, const size_t depth) const {
  std::shared_ptr<Object> hitObject;
  float tMin;

  std::tie(hitObject, tMin) = searchNearestIntersection(ray);

  // returns if nothing has been hit
  if (!hitObject)
    return {0,0,0};

  if (depth < 1)
    return {0,0,0};

  const Vec3 hitPoint = ray.origin + tMin * ray.direction;
  const Vec3 hitPointNormal = hitObject->normalAt(hitPoint);
  const Ray reflectedRay = {
      hitPoint, ray.direction -
                    2.0f * hitPointNormal.dot(ray.direction) * hitPointNormal};
  const auto reflectedRayHitInfo = castRay(reflectedRay, depth - 1);

  // FIXME: `typeid` might be expensive, we must benchmark that part
  const Vec2 uvMapping =
      typeid(hitObject->texture.get()) == typeid(UniformTexture)
          ? Vec2{0.0f, 0.0f}
          : hitObject->uvMapping(hitPoint);
  // FIXME-END

  const auto &objTexture = hitObject->texture;

  Vec3 objColor;
  for (const auto &light : scene.lights) {
    std::shared_ptr<Object> hitObjectBeforeLight;
    float tObjectBeforeLight;

    Vec3 vHitPointToLight = light->position - hitPoint;
    Vec3 vHitPointToLightDirection = vHitPointToLight.normalized();
    const float tLight =
        vHitPointToLightDirection.x() > EPSILON
            ? vHitPointToLight.x() / vHitPointToLightDirection.x()
            : vHitPointToLightDirection.y() > EPSILON
                  ? vHitPointToLight.y() / vHitPointToLightDirection.y()
                  : vHitPointToLight.z() / vHitPointToLightDirection.z();

    const Ray rayToLight{hitPoint, vHitPointToLightDirection};
    std::tie(hitObjectBeforeLight, tObjectBeforeLight) =
        searchNearestIntersection(
            rayToLight,
            [tLight](const std::shared_ptr<Object> &, float t) -> bool {
              return t < tLight;
            });

    // FIXME: binary shadow detection (shadow / not shadow) will result in
    //        cut-edged shadows, we have to replace that by some kind of
    //        progressive shadow
    if (tObjectBeforeLight < tLight)
      continue;
    // FIXME-END

    const auto _C = objTexture->colorAt(uvMapping);
    const auto _KD = objTexture->kdAt(uvMapping);
    const auto _KS = objTexture->ksAt(uvMapping);
    const auto _NS = objTexture->nsAt(uvMapping);
    const auto _LI = light->intensity / tLight;
    const auto _N = hitObject->normalAt(hitPoint);

    const auto _diffuseLight =
        _KD * std::max(0.0f, _N.dot(rayToLight.direction)) * _LI;

    const auto _specularLight =
        _KS * _LI *
        std::pow(
            std::max(0.0f, reflectedRay.direction.dot(rayToLight.direction)),
            _NS);

    objColor += _C * _diffuseLight + reflectedRayHitInfo * _specularLight;
  }

  return objColor.majored(1.0f);
}

std::pair<const std::shared_ptr<Object> &, float>
Renderer::searchNearestIntersection(
    const Ray &ray,
    const std::function<bool(const std::shared_ptr<Object> &, float)>
        &stopException) const {
  std::shared_ptr<Object> hitObject = nullptr;
  float tMin = std::numeric_limits<float>::max();

  // Search the nearest collided object
  for (const auto &obj : scene.objects) {
    const auto [uv, t] = obj->intersect(ray);

    if (t <= EPSILON || t >= tMin)
      continue;

    if (stopException(obj, t))
      return {obj, t};

    // FIXME: doing this will increase the ref counter, and thus call
    //  `thread.lock()`, which might be expensive we should replace
    //  `std::shared_ptr` by raw pointers
    hitObject = obj;
    // FIXME-END
    tMin = t;
  }

  return {hitObject, tMin};
}
