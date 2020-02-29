//
// Created by ultra on 2/14/20.
//

#pragma once

#include "ray.h"
#include "texture.h"
#include <memory>
#include <optional>
#include <utility>

using Intersection = std::pair<Vec2, float>;

class Object {
public:
  virtual ~Object() = default;

  explicit Object(TextureMaterial *texture) : texture(texture) {}

  [[nodiscard]] virtual Intersection intersect(const Ray &r) const = 0;
  [[nodiscard]] virtual Vec3 normalAt(const Vec3 &p) const = 0;
  [[nodiscard]] virtual Vec2 uvMapping(const Vec3 &p) const = 0;
  [[nodiscard]] virtual bool contains(const Vec3 &p) const = 0;

  const TextureMaterial *texture;

protected:
};

class Sphere : public Object {
public:
  Sphere(TextureMaterial *texture, const float radius,
         const Vec3 center)
      : Object::Object(texture), center(center), radius(radius),
        radius_square_(radius * radius) {}

  [[nodiscard]] Intersection intersect(const Ray &r) const final;
  [[nodiscard]] Vec3 normalAt(const Vec3 &p) const final;
  [[nodiscard]] Vec2 uvMapping(const Vec3 &p) const final;
  [[nodiscard]] bool contains(const Vec3 &p) const final;

  const Vec3 center;
  const float radius;

private:
  const float radius_square_;
};

class Plane : public Object {
public:
  Plane(TextureMaterial *texture, Vec3 normal, Vec3 samplePoint)
      : Object::Object(texture), normal_(normal.normalized()),
        p0_(samplePoint) {}

  [[nodiscard]] Intersection intersect(const Ray &r) const final;
  [[nodiscard]] Vec3 normalAt(const Vec3 &) const final;
  [[nodiscard]] Vec2 uvMapping(const Vec3 &p) const final;
  [[nodiscard]] bool contains(const Vec3 &p) const final;

private:
  Vec3 normal_;
  Vec3 p0_;
};
