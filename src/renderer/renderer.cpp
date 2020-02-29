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
  const auto [obj, uvObj, tObj] = searchNearestIntersection(ray);

  if (!obj)
    return {0, 0, 0};

  const Vec3 P = ray.origin + tObj * ray.direction;
  const Vec3 N = obj->normalAt(P);

  const Ray reflectedRay = {P, ray.direction - 2.0f * N.dot(ray.direction) * N};
  const Vec3 reflectedRayColor =
      depth == 1 ? Vec3{0, 0, 0} : castRay(reflectedRay, depth - 1);

  const auto C = obj->texture->colorAt(uvObj);
  const auto KD = obj->texture->kdAt(uvObj);
  const auto KS = obj->texture->ksAt(uvObj);
  const auto NS = obj->texture->nsAt(uvObj);

  Vec3 objColor;
  for (const auto &light : scene.lights) {
    Vec3 vHitPointToLight = light->position - P;
    Vec3 vHitPointToLightDirection = vHitPointToLight.normalized();
    const float tLight =
        vHitPointToLightDirection.x() > EPSILON
            ? vHitPointToLight.x() / vHitPointToLightDirection.x()
            : vHitPointToLightDirection.y() > EPSILON
                  ? vHitPointToLight.y() / vHitPointToLightDirection.y()
                  : vHitPointToLight.z() / vHitPointToLightDirection.z();

    const Ray rayToLight{P, vHitPointToLightDirection};
    const auto [hitObjectBeforeLight, uv, tObjectBeforeLight] =
        searchNearestIntersection(
            rayToLight,
            [tLight](const Object *, float t) -> bool { return t < tLight; });

    // FIXME: binary shadow detection (shadow / not shadow) will result in
    //        cut-edged shadows, we have to replace that by some kind of
    //        progressive shadow
    if (tObjectBeforeLight < tLight)
      continue;
    // FIXME-END


    const auto _LI = light->intensity / tLight;

    const auto _diffuseLight =
        KD * std::max(0.0f, N.dot(rayToLight.direction)) * _LI;

    const auto _specularLight =
        KS * _LI *
        std::pow(
            std::max(0.0f, reflectedRay.direction.dot(rayToLight.direction)),
            NS);

    objColor += C * _diffuseLight + reflectedRayColor * _specularLight;
  }

  return objColor.majored(1.0f);
}
std::tuple<const Object *, Vec2, float> Renderer::searchNearestIntersection(
    const Ray &ray,
    const std::function<bool(const Object *, float)> &stopException) const {

  Object *hitObject = nullptr;
  float tMin = std::numeric_limits<float>::max();
  Vec2 uvMin = {-1.0f, -1.0f};

  // Search the nearest collided object
  for (const auto &obj : scene.objects) {
    const auto [uv, t] = obj->intersect(ray);

    if (t <= EPSILON || t >= tMin)
      continue;

    if (stopException(obj, t))
      return {obj, uv, t};

    hitObject = obj;
    tMin = t;
    uvMin = uv;
  }

  return {hitObject, uvMin, tMin};
}
