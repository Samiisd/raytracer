#include <camera.h>
#include <fstream>
#include <iostream>
#include <object.h>
#include <renderer.h>
#include <texture.h>

int main() {
  const size_t imHeight = 1080, imWidth = 1920;

  const Camera cam{imHeight,  imWidth, {0, 1, -4}, {0, 0, 0},
                   {0, 1, 0}, 10,    70,         16.0f / 9.0f};

  Scene scene(cam);
  auto white = std::make_shared<UniformTexture>(UniformTexture({1, 1, 1}, 1, 1, 1, 30, 0));
  auto red = std::make_shared<UniformTexture>(UniformTexture({1, 0, 0}, 2, 1, 1, 5, 0));
  auto green = std::make_shared<UniformTexture>(UniformTexture({0, 1, 0}, 2, 7, 1, 20, 0));
  auto blue = std::make_shared<UniformTexture>(UniformTexture({0, 0.05, 1}, 2, 5, 1, 10, 0));
  auto cyan = std::make_shared<UniformTexture>(UniformTexture({0, 1, 1}, 3, 5, 1, 25, 0));
  auto yellow = std::make_shared<UniformTexture>(UniformTexture({1, 1, 0}, 4, 5, 1, 25, 0));

  scene.objects = {
      std::make_shared<Plane>(Plane(white, Vec3(0,1,0).normalized(), {0,0,0})),
      std::make_shared<Plane>(Plane(white, Vec3(0,0,-1).normalized(), {0,0,5})),
      std::make_shared<Plane>(Plane(red, Vec3(1,0,0).normalized(), {-3,0,0})),
      std::make_shared<Plane>(Plane(green, Vec3(-1,0,0).normalized(), {5,0,0})),

      std::make_shared<Sphere>(Sphere(blue, 0.5, {0,.75,0})),
      std::make_shared<Sphere>(Sphere(green, 0.5, {-1,.5,0})),
      std::make_shared<Sphere>(Sphere(red, 0.5, {1,.5,0})),
      std::make_shared<Sphere>(Sphere(blue, 0.7, {2,1,-1})),
      std::make_shared<Sphere>(Sphere(yellow, 0.1, {-1,0.6,-1.5})),
      std::make_shared<Sphere>(Sphere(cyan, 0.3, {0.5,0.3,-1.5})),
  };

  scene.lights.push_back(std::make_shared<Light>(Light({5, 3, -5}, {1,1,1}, 3)));
  scene.lights.push_back(std::make_shared<Light>(Light({-1, 2, 2})));

  auto engine = Renderer(scene, imHeight, imWidth);

  std::ofstream("/home/ultra/projects/raytracer/result.ppm") << engine.render(2);//, 10);

  return 0;
}
