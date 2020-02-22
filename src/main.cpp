#include <camera.h>
#include <fstream>
#include <iostream>
#include <object.h>
#include <renderer.h>
#include <texture.h>

int main() {
  const size_t imHeight = 1080/2, imWidth = 1920/2;

  const Camera cam{imHeight,  imWidth, {0, 1, -4}, {0, 0, 0},
                   {0, 1, 0}, 10,    60,         16.0f / 9.0f};

  Scene scene(cam);
  auto white = std::make_shared<UniformTexture>(UniformTexture({1, 1, 1}, 1, 5, 1, 1, 0));
  auto red = std::make_shared<UniformTexture>(UniformTexture({1, 0, 0}, 1, 1, 1, 10, 0));
  auto green = std::make_shared<UniformTexture>(UniformTexture({0, 1, 0}, 1, 7, 1, 6, 0));
  auto blue = std::make_shared<UniformTexture>(UniformTexture({0, 0.05, 1}, 10, 5, 1, 5, 0));

  scene.objects = {
      std::make_shared<Plane>(Plane(white, Vec3(0,1,0).normalized(), {0,0,0})),
      std::make_shared<Plane>(Plane(white, Vec3(0,0,-1).normalized(), {0,0,5})),
      std::make_shared<Plane>(Plane(red, Vec3(1,0,0).normalized(), {-3,0,0})),
      std::make_shared<Plane>(Plane(green, Vec3(-1,0,0).normalized(), {5,0,0})),

      std::make_shared<Sphere>(Sphere(blue, 0.5, {0,.75,0})),
      std::make_shared<Sphere>(Sphere(red, 0.5, {-1,.5,0})),
      std::make_shared<Sphere>(Sphere(green, 0.5, {1,.5,0})),
      std::make_shared<Sphere>(Sphere(blue, 0.5, {2,1,-2})),
  };

  scene.lights.push_back(std::make_shared<Light>(Light({1, 1, -2})));
  scene.lights.push_back(std::make_shared<Light>(Light({-1, 2, 2})));

  auto engine = Renderer(scene, imHeight, imWidth);

  std::ofstream("/home/ultra/projects/raytracer/result.ppm") << engine.render(4);//, 10);

  return 0;
}
