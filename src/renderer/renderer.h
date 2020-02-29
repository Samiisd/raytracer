#pragma once

#include <image.h>
#include <scene.h>

#include <functional>
#include <random>
#include <utility>

class Renderer {
public:
  explicit Renderer(Scene scene, size_t imHeight, size_t imWidth)
      : scene(std::move(scene)), imHeight(imHeight), imWidth(imWidth) {}

  [[nodiscard]] Image render(size_t depth = 1) const;

  const Scene scene;
  const size_t imHeight, imWidth;

private:
  [[nodiscard]] std::pair<const std::shared_ptr<Object> &, float>
  searchNearestIntersection(
      const Ray &ray,
      const std::function<bool(const std::shared_ptr<Object> &, float)>
          &stopException = [](const std::shared_ptr<Object> &, float) -> bool {
        return false;
      }) const;
  [[nodiscard]] Vec3 castRay(const Ray &ray, size_t depth = 0) const;
};
