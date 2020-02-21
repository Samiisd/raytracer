//
// Created by ultra on 2/20/20.
//

#include "renderer.h"

Image Renderer::render() const {
  Image result(imHeight, imWidth);

  const Camera &camera = scene.camera;

  // Iterate over all pixels of the image
  for (size_t y = 0; y < imHeight; y++) {
    for (size_t x = 0; x < imWidth; x++) {

      // Create a ray going from the camera to the 2D-pixel projection in 3D
      // world
      const Ray r = {camera.eye(),
                     (camera.pixelToWorld(y, x) - camera.eye()).normalized()};

      result(y, x) = castRay(r).color;
    }
  }

  return result;
}

Renderer::rayHitInfo Renderer::castRay(const Ray &ray,
                                       const size_t depth) const {
  std::shared_ptr<Object> hitObject = nullptr;
  float tMin = std::numeric_limits<float>::max();

  // Search the nearest collided object
  for (const auto &obj : scene.objects) {
    float t = obj->intersect(ray);
    if (t >= 0.001 && t < tMin) {
      // FIXME: doing this will increase the ref counter, and thus call
      //  `thread.lock()`, which might be expensive we should replace
      //  `std::shared_ptr` by raw pointers
      hitObject = obj;
      // FIXME-END
      tMin = t;
    }
  }

  // returns if nothing has been hit
  if (!hitObject)
    return rayHitInfo{{0, 0, 0}, std::min(tMin, -1.0f)};

  const Vec3 hitPoint = ray.origin + tMin * ray.direction;
  const Vec3 hitPointNormal = hitObject->normalAt(hitPoint);
  const auto reflectedRayHitInfo =
      depth > 0 ? castRay({hitPoint, ray.direction * 2.0f *
                                         ray.direction.cross(-hitPointNormal) *
                                         hitPointNormal})
                : rayHitInfo{{0, 0, 0}, -1.0f};

  // FIXME: `typeid` might be expensive, we must benchmark that part
  const Vec2 uvMapping = typeid(hitObject->texture) == typeid(UniformTexture)
                             ? Vec2{0.0f, 0.0f}
                             : hitObject->uvMapping(hitPoint);
  // FIXME-END

  const auto &objTexture = hitObject->texture;

  Vec3 objColor;
  for (const auto &light : scene.lights) {
    const Ray rayToLight{hitPoint, (light->position - hitPoint).normalized()};

    // FIXME: binary shadow detection (shadow / not shadow) will result in
    //        cut-edged shadows, we have to replace that by some kind of
    //        progressive shadow
    const auto hitLight = castRay(rayToLight);
    if (!hitLight.hasHit())
      continue;
    // FIXME-END

    objColor += objTexture->colorAt(uvMapping) *
                    (objTexture->kdAt(uvMapping) *
                     (hitObject->normalAt(hitPoint) * rayToLight.direction) *
                     light->intensity) +
                objTexture->ksAt(uvMapping) * light->intensity *
                    (reflectedRayHitInfo.color * light->intensity);
  }

  return {objColor, tMin};
}
