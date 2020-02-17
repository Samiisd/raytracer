#include <camera.h>
#include <image.h>
#include <iostream>
#include <object.h>
#include <ray.h>

int _test() {
  const Sphere s(10.0f, {1,2,3});

  float dx, dy, dz;
  std::cout << "ray_origin = ";
  std::cin >> dx >> dy >> dz;
  const Vector3 rayOrigin{dx, dy, dz};

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
  while (true) {
    std::cout << "ray_direction = ";

    std::cin >> dx >> dy >> dz;

    const Ray ray{rayOrigin, Vector3(dx,dy,dz).normalized()};
    float t = s.intersect(ray);
    if (t >= 0)
      std::cout << "intersection point: " << ray.origin + t * ray.direction << std::endl;
    else
      std::cout << "No intersection (t=" << t << ")" << std::endl;
  }
#pragma clang diagnostic pop
  return 0;
}


int main() {
  const Sphere s(10.0f, {0, 0, 0});
  const Camera cam{{20, 0, 0}, {0, 0, 0}, {0, 1, 0}};

}
