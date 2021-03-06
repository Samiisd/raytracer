#include <camera.h>
#include <chrono>
#include <fstream>
#include <iostream>
#include <object.h>
#include <renderer.h>
#include <texture.h>

using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;

int main() {
  const size_t imHeight = 720ULL, imWidth = 1280ULL;

  const Camera cam{imHeight,  imWidth, {0, 1, -4}, {0, 0, 0},
                   {0, 1, 0}, 90.0,      70,         16.0f / 9.0f};

  Scene scene(cam);
  auto white = new UniformTexture({1, 1, 1}, 1, 1, 1, 30, 0);
  auto red = new UniformTexture({1, 0, 0}, 2, 1, 1, 5, 0);
  auto green = new UniformTexture({0, 1, 0}, 2, 7, 1, 20, 0);
  auto blue = new UniformTexture({0, 0.05, 1}, 2, 5, 1, 10, 0, 0.85);
  auto cyan = new UniformTexture({0, 1, 1}, 3, 5, 1, 25, 0);
  auto yellow = new UniformTexture({1, 1, 0}, 4, 5, 1, 25, 0);

  scene.objects = {
      new Plane(white, Vec3(0, 1, 0).normalized(), {0, 0, 0}),
      new Plane(white, Vec3(0, 0, -1).normalized(), {0, 0, 5}),
      new Plane(red, Vec3(1, 0, 0).normalized(), {-3, 0, 0}),
      new Plane(green, Vec3(-1, 0, 0).normalized(), {5, 0, 0}),

      new Sphere(blue, 0.5, {0, .75, 0}),
      new Sphere(green, 0.5, {-1, .5, 0}),
      new Sphere(red, 0.5, {1, .5, 0}),
      new Sphere(blue, 0.7, {2, 1, -1}),
      new Sphere(yellow, 0.1, {-1, 0.6, -1.5}),
      new Sphere(cyan, 0.3, {0.5, 0.3, -1.5}),
  };

  scene.lights = {new Light({4.99, 3, -5}, {1, 1, 1}, 3),
                  new Light({-1, 2, 2})};

  auto engine = Renderer(scene, imHeight, imWidth);

  std::cout << "generating scene...\n";
  const auto startTime = std::chrono::high_resolution_clock::now();
  const Image result = engine.render(3, 25);
  const auto endTime = std::chrono::high_resolution_clock::now();
  std::cout << "took: "
            << duration_cast<duration<double, std::milli>>(endTime - startTime)
                   .count()
            << " ms ("
            << duration_cast<duration<double, std::nano>>(endTime - startTime)
                       .count() /
                   (double)(imHeight * imWidth)
            << " ns/pixel)" << std::endl;

  std::ofstream("/home/ultra/projects/raytracer/result.ppm") << result;

  while (!scene.lights.empty()) {
    delete scene.lights.back();
    scene.lights.pop_back();
  }

  while (!scene.objects.empty()) {
    delete scene.objects.back();
    scene.objects.pop_back();
  }

  delete white;
  delete red;
  delete green;
  delete blue;
  delete yellow;
  delete cyan;

  return 0;
}
