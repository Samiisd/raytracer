#pragma once

#include <cmath>
#include <iostream>
#include <optional>

using T = float;

class Vec3 {
public:
  Vec3() = default;
  Vec3(const T x, const T y, const T z) : x_(x), y_(y), z_(z) {}

  friend std::ostream &operator<<(std::ostream &out, const Vec3 &p) {
    out << "{" << p.x_ << "; " << p.y_ << "; " << p.z_ << "}";
    return out;
  }

  Vec3 operator*(const T &l) const { return Vec3(x_ * l, y_ * l, z_ * l); }

  Vec3 operator*(const Vec3 &v) const {
    return Vec3(x_ * v.x_, y_ * v.y_, z_ * v.z_);
  }

  Vec3 operator+(const Vec3 &v) const {
    return Vec3(x_ + v.x_, y_ + v.y_, z_ + v.z_);
  }

  Vec3 operator-(const Vec3 &v) const {
    return Vec3(x_ - v.x_, y_ - v.y_, z_ - v.z_);
  }

  [[nodiscard]] T dot(const Vec3 &v) const {
    return x_ * v.x_ + y_ * v.y_ + z_ * v.z_;
  }

  [[nodiscard]] Vec3 cross(const Vec3 &v) const {
    return {y_ * v.z_ - z_ * v.y_, x_ * v.z_ - z_ * v.x_,
            x_ * v.y_ - y_ * v.x_};
  }

  [[nodiscard]] Vec3 normalized() {
    if (!norm_.has_value())
      norm_ = std::sqrt(x_ * x_ + y_ * y_ + z_ * z_);

    float norm = *norm_;
    return {x_ / norm, y_ / norm, z_ / norm};
  }

  [[nodiscard]] T x() const { return x_; }
  [[nodiscard]] T y() const { return y_; }
  [[nodiscard]] T z() const { return z_; }

private:
  T x_, y_, z_;
  std::optional<float> norm_;
};

inline Vec3 operator*(float f, const Vec3 &v) { return v * f; }

struct Ray {
  Vec3 origin;
  Vec3 direction;
};
