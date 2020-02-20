//
// Created by ultra on 2/14/20.
//

#pragma once

#include "image.h"
#include "ray.h"

class Light {
public:
  explicit Light(const Vec3 &position, const Color &color = Color{255, 255, 255},
        float intensity = 1.0f)
      : position(position), color(color), intensity(intensity) {}

  Vec3 position;
  Color color;
  float intensity;

protected:
};

class PointLight : public Light {
public:
  using Light::Light;
private:
};

void a() { PointLight b({1, 2, 3}); }
