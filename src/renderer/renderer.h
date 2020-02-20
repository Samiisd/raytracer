//
// Created by ultra on 2/20/20.
//

#pragma once

#include <image.h>
#include <scene.h>

#include <utility>

class Renderer {
public:
  explicit Renderer(Scene scene, size_t imHeight, size_t imWidth) : scene(std::move(scene)), imHeight(imHeight), imWidth(imWidth) {}

  [[nodiscard]] Image render() const;

  const Scene scene;
  const size_t imHeight, imWidth;
private:
};
