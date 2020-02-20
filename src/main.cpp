#include <camera.h>
#include <image.h>
#include <iostream>
#include <object.h>
#include <ray.h>

int main() {
  const Sphere s(10.0f, {0, 0, 0});
  Image result(1080, 1920);
  const Camera cam{static_cast<float>(result.height),
                   static_cast<float>(result.width),
                   {60, 0, 0},
                   {0, 0, 0},
                   Vec3(0, 1, 0).normalized(),
                   0.05,
                   20,
                   16.0f/9.0f};

  for (size_t y = 0; y < result.height; y++) {
    for (size_t x = 0; x < result.width; x++) {
      const Ray r = {cam.eye,(cam.pixelToRay(static_cast<float>(y), static_cast<float>(x)) - cam.eye).normalized()};
      float t = s.intersect(r);
      if (t >= 0) {
        result(y, x) = {255, 255, 255};
      }
    }
  }

  std::cout << result;
}
