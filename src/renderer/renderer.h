#pragma once

#include <image.h>
#include <scene.h>

#include <functional>
#include <random>
#include <utility>

class Renderer {
public:
  explicit Renderer(Scene scene, size_t imHeight, size_t imWidth)
      : scene(std::move(scene)), imHeight(imHeight), imWidth(imWidth), rd_(),
        gen_(rd_()), dis_(std::uniform_real_distribution<>(0.0f, 1.0f)) {}

  [[nodiscard]] Image render(size_t depth = 1, size_t nbAntiAliasingRay = 0, bool multithreads = true);

  const Scene scene;
  const size_t imHeight, imWidth;

private:
  [[nodiscard]] std::tuple<const Object *, Vec2, float>
  searchNearestIntersection(
      const Ray &ray,
      const std::function<bool(const Object *, float)> &stopException =
          [](const Object *, float) -> bool { return false; }) const;

  [[nodiscard]] Vec3 castRay(const Ray &ray, size_t depth = 0) const;

  std::random_device rd_;
  std::mt19937 gen_;
  std::uniform_real_distribution<> dis_;
};
