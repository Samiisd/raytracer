//
// Created by ultra on 2/14/20.
//

#pragma once

#include "image.h"
#include "ray.h"

class Light {
public:
  explicit Light(const Vector3 &position, const Pixel &color = Pixel{255, 255, 255},
        float intensity = 1.0f)
      : position(position), color(color), intensity(intensity) {}

  Vector3 position;
  Pixel color;
  float intensity;

protected:
};

class PointLight : public Light {
public:
  using Light::Light;
private:
};

void a() { PointLight b({1, 2, 3}); }
