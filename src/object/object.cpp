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

Intersection Sphere::intersect(const Ray &r) const {
  float t0, t1;

  const Vec3 L = r.origin - center;

  const float a = 1.0f, b = 2.0f * r.direction.dot(L),
              c = L.dot(L) - radius_square_;

  if (!solveQuadratic(a, b, c, t0, t1))
    return {{0, 0}, -1.0f};

  return {{0, 0}, t0 < 0 ? t1 : t0};
}

Vec3 Sphere::normalAt(const Vec3 &p) const { return (p - center).normalized(); }

Intersection Plane::intersect(const Ray &r) const {
  const float nu = normal_.dot(r.direction);

  if (std::fabs(nu) < EPSILON)
    return {{0, 0}, -1.0f};

  const auto t = normal_.dot(p0_ - r.origin) / nu;
  return {{0, 0}, t};
}

Vec3 Plane::normalAt(const Vec3 &) const { return normal_; }
