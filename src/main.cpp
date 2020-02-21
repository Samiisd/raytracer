#include <camera.h>
#include <iostream>
#include <object.h>
#include <renderer.h>
#include <texture.h>

int main() {
  const size_t imHeight = 1080, imWidth = 1920;

  const Camera cam{imHeight,  imWidth, {60, 0, 0}, {0, 0, 0},
                   {0, 1, 0}, 0.05,    60,         16.0f / 9.0f};

  Scene scene(cam);
  auto blue = std::make_shared<UniformTexture>(UniformTexture({0, 0.05, 1}, 1, 1, 1, 0));
  scene.objects.push_back(std::make_shared<Sphere>(Sphere{blue, 10.0f, {0, 0, 0}}));

  const auto engine = Renderer(scene, imHeight, imWidth);

  std::cout << engine.render();
}
