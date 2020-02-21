#include <camera.h>
#include <iostream>
#include <object.h>
#include <renderer.h>
#include <texture.h>

int main() {
  const size_t imHeight = 1080, imWidth = 1920;

  const Camera cam{imHeight,  imWidth, {30, 0, 0}, {0, 0, 0},
                   {0, 1, 0}, 1,    40,         16.0f / 9.0f};

  Scene scene(cam);
  auto red = std::make_shared<UniformTexture>(UniformTexture({1, 0, 0}, 1, 1, 1, 10, 0));
  auto green = std::make_shared<UniformTexture>(UniformTexture({0, 1, 0}, 1, 1, 1, 6, 0));
  auto blue = std::make_shared<UniformTexture>(UniformTexture({0, 0.05, 1}, 1, 1, 1, 3, 0));
  scene.objects.push_back(std::make_shared<Sphere>(Sphere{red, 10.0f, {0, 0, 0}}));
  scene.objects.push_back(std::make_shared<Sphere>(Sphere{green, 5.0f, {0, 15, 0}}));
  scene.objects.push_back(std::make_shared<Sphere>(Sphere{blue, 13.0f, {12, -6, -13}}));
  scene.lights.push_back(std::make_shared<Light>(Light({25, 20, 5})));

  const auto engine = Renderer(scene, imHeight, imWidth);

  std::cout << engine.render();
  return 0;
}
