//
// Created by ultra on 2/14/20.
//

#include "object.h"

static bool solveQuadratic(const float &a, const float &b, const float &c,
                           float &x0, float &x1) {
  float discriminant = b * b - 4 * a * c;

  if (discriminant < 0)
    return false;
  else if (discriminant == 0)
    x0 = x1 = -0.5f * b / a;
  else {
    float q = (b > 0) ? -0.5f * (b + std::sqrt(discriminant))
                      : -0.5f * (b - std::sqrt(discriminant));
    x0 = q / a;
    x1 = c / q;
  }

  if (x0 > x1)
    std::swap(x0, x1);

  return true;
}

float Sphere::intersect(const Ray &r) const {
  float t0, t1;

  const Vec3 L = r.origin - center;

  const float a = 1.0f, b = 2.0f * r.direction.dot(L),
              c = L.dot(L) - radius_square_;

  if (!solveQuadratic(a, b, c, t0, t1))
    return -1.0f;

  return t0 < 0 ? t1 : t0;
}

Vec3 Sphere::normalAt(const Vec3 &p) const { return (p - center).normalized(); }

Vec2 Sphere::uvMapping(const Vec3 &p) const {
  const Vec3 d = (center - p).normalized();
  return {static_cast<T>(0.5f + (std::atan2(d.z(), d.x()) / (2.0f * M_PI))),
          static_cast<T>(0.5f - (std::asin(d.y()) / M_PI))};
}
bool Sphere::contains(const Vec3 &p) const {
  const Vec3 distance = p - center;
  return std::fabs((distance * distance).sum() - radius_square_) < EPSILON;
}

float Plane::intersect(const Ray &r) const {
    const float nu = normal_.dot(r.direction);

    if (std::fabs(nu) < EPSILON)
      return this->contains(r.origin) ? 0.0f : -1.0f;

    const auto t = normal_.dot(p0_ - r.origin)/nu;
    return t;
}

Vec3 Plane::normalAt(const Vec3 &) const { return normal_; }

Vec2 Plane::uvMapping(const Vec3 &) const { return {}; }

bool Plane::contains(const Vec3 &p) const { return std::fabs(normal_.dot(p0_ - p)) < EPSILON; }
