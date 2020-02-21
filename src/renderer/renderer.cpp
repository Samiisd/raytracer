//
// Created by ultra on 2/20/20.
//

#include "renderer.h"
#include <numeric>
#include <typeinfo>

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

Renderer::hitPoint Renderer::castRay(const Ray &ray, const size_t depth) const {

  std::shared_ptr<Object> hitObject = nullptr;
  float tMin = std::numeric_limits<float>::max();

  // Search the nearest collided object
  for (const auto &obj : scene.objects) {
    float t = obj->intersect(ray);
    if (t >= 0 && t < tMin)
      // FIXME: doing this will increase the ref counter, and thus call
      //  `thread.lock()`, which might be expensive we should replace
      //  `std::shared_ptr` by raw pointers
      hitObject = obj;
    // FIXME-END
  }

  if (!hitObject)
    return hitPoint{{0, 0, 0}, std::min(tMin, -1.0f)};

  // FIXME: `typeid` might be expensive, we must benchmark that part
  const Vec2 uvMapping =
      typeid(hitObject->texture) == typeid(UniformTexture)
          ? Vec2{0.0f, 0.0f}
          : hitObject->uvMapping(ray.origin + tMin * ray.direction);
  // FIXME-END

  // Calculate object illumination
  Vec3 objColor = hitObject->texture->colorAt(uvMapping);

  // FIXME: Compute object illumination
  // FIXME-END

  if (depth != 0) {
    // FIXME: should cast the reflected ray
  }

  return {objColor, tMin};
}
