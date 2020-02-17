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
  Vector3(const T x, const T y, const T z) : _x(x), _y(y), _z(z) {
    _norm = std::sqrt(_x * _x + _y * _y + _z * _z);
  }

  friend std::ostream &operator<<(std::ostream &out, const Vector3 &p) {
    out << "{" << p._x << "; " << p._y << "; " << p._z << "}";
    return out;
  }

  Vector3 operator*(const T &l) const {
    return Vector3(_x * l, _y * l, _z * l);
  }

  Vector3 operator+(const Vector3 &v) const {
    return Vector3(_x + v._x, _y + v._y, _z + v._z);
  }

  Vector3 operator-(const Vector3 &v) const {
    return Vector3(_x - v._x, _y - v._y, _z - v._z);
  }

  T dot(const Vector3 &v) const { return _x * v._x + _y * v._y + _z * v._z; }

  [[nodiscard]] Vector3 normalized() const {
    return Vector3(_x / _norm, _y / _norm, _z / _norm);
  }

private:
  T _x, _y, _z;
  T _norm;
};

inline Vector3 operator*(float f, const Vector3 &v) { return v * f; }

struct Ray {
  Vector3 origin;
  Vector3 direction;
};

#endif // TEMPLATE_ULTRA_VECTOR_H
