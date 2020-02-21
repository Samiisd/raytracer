//
// Created by ultra on 2/20/20.
//

#pragma once

#include <scene.h>
#include <image.h>

#include <utility>

class Renderer {
public:
  explicit Renderer(Scene scene, size_t imHeight, size_t imWidth)
      : scene(std::move(scene)), imHeight(imHeight), imWidth(imWidth) {}

  [[nodiscard]] Image render() const;

  const Scene scene;
  const size_t imHeight, imWidth;

private:
  struct hitPoint {
    const Vec3 color = {0.0f, 0.0f, 0.0f};
    const float t = -1.0f;

    [[nodiscard]] bool hasHit() const {
      return t < 0.0f;
    }
  };

  [[nodiscard]] hitPoint castRay(const Ray &ray, size_t depth = 0) const;
};
