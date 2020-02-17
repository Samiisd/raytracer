//
// Created by ultra on 2/14/20.
//

#pragma once

#include "ray.h"
#include "texture.h"
#include <optional>

class Object {
public:
  [[nodiscard]] virtual float intersect(const Ray &r) const = 0;
  [[nodiscard]] virtual Vector3 normalAt(const Vector3 &p) const = 0;
  [[nodiscard]] virtual TextureMaterial textureAt(const Vector3 &p) const = 0;

protected:
};

class Sphere : public Object {
public:
  Sphere(const float radius, const Vector3 center)
      : radius(radius), center(center), _radius_square(radius*radius) {}

  [[nodiscard]] float intersect(const Ray &r) const override;
  [[nodiscard]] Vector3 normalAt(const Vector3 &p) const override;
  [[nodiscard]] TextureMaterial textureAt(const Vector3 &p) const override;

  const float radius;
  const Vector3 center;

private:
  const float _radius_square;
};
