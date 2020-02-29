#include <camera.h>
#include <fstream>
#include <iostream>
#include <object.h>
#include <renderer.h>
#include <texture.h>

int main() {
  const size_t imHeight = 1080 / (1 << 3), imWidth = 1920 / (1 << 3);

  const Camera cam{imHeight,  imWidth, {0, 1, -4}, {0, 0, 0},
                   {0, 1, 0}, 10,      70,         16.0f / 9.0f};

  Scene scene(cam);
  auto white = new UniformTexture({1, 1, 1}, 1, 1, 1, 30, 0);
  auto red = new UniformTexture({1, 0, 0}, 2, 1, 1, 5, 0);
  auto green = new UniformTexture({0, 1, 0}, 2, 7, 1, 20, 0);
  auto blue = new UniformTexture({0, 0.05, 1}, 2, 5, 1, 10, 0);
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

  scene.lights = {new Light({5, 3, -5}, {1, 1, 1}, 3), new Light({-1, 2, 2})};

  auto engine = Renderer(scene, imHeight, imWidth);

  std::ofstream("/home/ultra/projects/raytracer/result.ppm")
      << engine.render(2);

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
