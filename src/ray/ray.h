//
// Created by ultra on 2/14/20.
//

#ifndef TEMPLATE_ULTRA_VECTOR_H
#define TEMPLATE_ULTRA_VECTOR_H

#include <cmath>
#include <iostream>

using T = float;

class Vector3 {
public:
  Vector3(const T x, const T y, const T z)
      : x(x), y(y), z(z), norm(std::sqrt(x * x + y * y + z * z)) {}

  friend std::ostream &operator<<(std::ostream &out, const Vector3 &p) {
    out << "{" << p.x << "; " << p.y << "; " << p.z << "}";
    return out;
  }

  Vector3 operator*(const T &l) const { return Vector3(x * l, y * l, z * l); }

  Vector3 operator*(const Vector3 &v) const {
    return Vector3(x * v.x, y * v.y, z * v.z);
  }

  Vector3 operator+(const Vector3 &v) const {
    return Vector3(x + v.x, y + v.y, z + v.z);
  }

  Vector3 operator-(const Vector3 &v) const {
    return Vector3(x - v.x, y - v.y, z - v.z);
  }

  [[nodiscard]] T dot(const Vector3 &v) const {
    return x * v.x + y * v.y + z * v.z;
  }

  [[nodiscard]] Vector3 cross(const Vector3 &v) const {
    return {y * v.z - z * v.y, x * v.z - z * v.x, x * v.y - y * v.x};
  }

  [[nodiscard]] Vector3 normalized() const {
    return Vector3(x / norm, y / norm, z / norm);
  }

  const T x, y, z;
  const T norm;
};

inline Vector3 operator*(float f, const Vector3 &v) { return v * f; }

struct Ray {
  Vector3 origin;
  Vector3 direction;
};

#endif // TEMPLATE_ULTRA_VECTOR_H
