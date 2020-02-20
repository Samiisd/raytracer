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

      // Create a ray going from the camera to the 2D-pixel projection in 3D world
      const Ray r = {camera.eye(),
                     (camera.pixelToWorld(y, x) - camera.eye()).normalized()};

      // Iterate over all object of the scene to check collision
      for (const auto& obj : scene.objects) {
        float t = obj->intersect(r);
        if (t >= 0) {
          result(y, x) = {255, 255, 255};
        }
      }
    }
  }

  return result;
}
