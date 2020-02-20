//
// Created by ultra on 2/14/20.
//

#ifndef TEMPLATE_ULTRA_VECTOR_H
#define TEMPLATE_ULTRA_VECTOR_H

#include <cmath>
#include <iostream>

using T = float;

class Vec3 {
public:
  Vec3(const T x, const T y, const T z)
      : x(x), y(y), z(z), norm(std::sqrt(x * x + y * y + z * z)) {}

  friend std::ostream &operator<<(std::ostream &out, const Vec3 &p) {
    out << "{" << p.x << "; " << p.y << "; " << p.z << "}";
    return out;
  }

  Vec3 operator*(const T &l) const { return Vec3(x * l, y * l, z * l); }

  Vec3 operator*(const Vec3 &v) const {
    return Vec3(x * v.x, y * v.y, z * v.z);
  }

  Vec3 operator+(const Vec3 &v) const {
    return Vec3(x + v.x, y + v.y, z + v.z);
  }

  Vec3 operator-(const Vec3 &v) const {
    return Vec3(x - v.x, y - v.y, z - v.z);
  }

  [[nodiscard]] T dot(const Vec3 &v) const {
    return x * v.x + y * v.y + z * v.z;
  }

  [[nodiscard]] Vec3 cross(const Vec3 &v) const {
    return {y * v.z - z * v.y, x * v.z - z * v.x, x * v.y - y * v.x};
  }

  [[nodiscard]] Vec3 normalized() const {
    return Vec3(x / norm, y / norm, z / norm);
  }

  const T x, y, z;
  const T norm;
};

inline Vec3 operator*(float f, const Vec3 &v) { return v * f; }

struct Ray {
  Vec3 origin;
  Vec3 direction;
};

#endif // TEMPLATE_ULTRA_VECTOR_H
