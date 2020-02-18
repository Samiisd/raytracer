#include <camera.h>
#include <image.h>
#include <iostream>
#include <object.h>
#include <ray.h>

int _test() {
  const Sphere s(10.0f, {1, 2, 3});

  float dx, dy, dz;
  std::cout << "ray_origin = ";
  std::cin >> dx >> dy >> dz;
  const Vector3 rayOrigin{dx, dy, dz};

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
  while (true) {
    std::cout << "ray_direction = ";

    std::cin >> dx >> dy >> dz;

    const Ray ray{rayOrigin, Vector3(dx, dy, dz).normalized()};
    float t = s.intersect(ray);
    if (t >= 0)
      std::cout << "intersection point: " << ray.origin + t * ray.direction
                << std::endl;
    else
      std::cout << "No intersection (t=" << t << ")" << std::endl;
  }
#pragma clang diagnostic pop
  return 0;
}

int main() {
  const Sphere s(10.0f, {0, 0, 0});
  Image result(200, 200);
  const Camera cam{static_cast<float>(result.height),
                   static_cast<float>(result.width),
                   {20, 1000, 0},
                   {0, 0, 0},
                   Vector3(0, 1, 0).normalized(),
                   10,
                   40,
                   40};

  for (size_t y = 0; y < result.height; y++) {
    for (size_t x = 0; x < result.width; x++) {
      //      if ((y % 100) == 0 && (x % 100) == 0)
      //        std::cout << Vector3{(float)x, (float)y, 0} << "->" <<
      //        cam.pixelToRay(y, x) << '\n';
      const Ray r = {cam.eye,(cam.pixelToRay(static_cast<float>(y), static_cast<float>(x)) - cam.eye).normalized()};
      float t = s.intersect(r);
      if (t >= 0) {
//        std::cout << "OMG, COLLISION AT: " << r.origin + t * r.direction<< std::endl;
        result(y, x) = {255, 255, 255};
      }
    }
  }

  std::cout << result;
}
