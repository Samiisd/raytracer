//
// Created by ultra on 2/14/20.
//

#ifndef TEMPLATE_ULTRA_VECTOR_H
#define TEMPLATE_ULTRA_VECTOR_H

#include <iostream>

template <class T> class Point3 {
public:
  T x, y, z;

  friend std::ostream &operator<<(std::ostream &out, const Point3<T> &p) {
    out << "(" << p.x << "; " << p.y << "; " << p.z << ")";
    return out;
  }
};


template <class T> class Vector3 {
public:
  Vector3(const T x, const T y, const T z) : x(x), y(y), z(z) {}
  T x = 0, y = 0, z = 0;

  friend std::ostream &operator<<(std::ostream &out, const Vector3<T> &p){
    out << "{" << p.x << "; " << p.y << "; " << p.z << "}";
    return out;
  }

  Vector3 operator*(const T &l) const {
    return Vector3(x*l, y*l, z*l);
  }

  Vector3 operator+(const Vector3<T> &v) const {
    return Vector3(x+v.x, y+v.y, z+v.z);
  }

  Vector3 operator-(const Vector3<T> &v) const {
    return Vector3(x-v.x, y-v.y, z-v.z);
  }
};

#endif // TEMPLATE_ULTRA_VECTOR_H
