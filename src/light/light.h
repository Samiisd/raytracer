//
// Created by ultra on 2/14/20.
//

#pragma once

#include "ray.h"
#include "texture.h"

class Light {
public:
  explicit Light(const Vec3 &position, const Vec3 &color = Vec3{1.0f, 1.0f, 1.0f},
                 float intensity = 1.0f)
      : position(position), color(color), intensity(intensity) {}

  Vec3 position;
  Vec3 color;
  float intensity;

protected:
};

class PointLight : public Light {
public:
  using Light::Light;

private:
};
