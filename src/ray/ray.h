#pragma once

#include <algorithm>
#include <cmath>
#include <iostream>
#include <optional>

using T = float;
const T EPSILON = 1.0e-4f;

class Vec2 {
public:
  Vec2() = default;
  Vec2(const T x, const T y) : x_(x), y_(y) {}

  friend std::ostream &operator<<(std::ostream &out, const Vec2 &p) {
    out << "{" << p.x_ << "; " << p.y_ << "; "
        << "}";
    return out;
  }

  Vec2 operator*(const T &l) const { return {x_ * l, y_ * l}; }

  Vec2 operator*(const Vec2 &v) const { return {x_ * v.x_, y_ * v.y_}; }
  Vec2 operator+(const Vec2 &v) const { return {x_ + v.x_, y_ + v.y_}; }
  Vec2 operator-(const Vec2 &v) const { return {x_ - v.x_, y_ - v.y_}; }
  Vec2 operator-() const { return {-x_, -y_}; }

  void operator+=(const Vec2 &v) {
    x_ += v.x_;
    y_ += v.y_;
  }

  [[nodiscard]] T dot(const Vec2 &v) const { return x_ * v.x_ + y_ * v.y_; }
  [[nodiscard]] T sum() const { return x_ + y_; }

  [[nodiscard]] float norm() {
    if (norm_ < 0.0f)
      norm_ = std::sqrt(x_ * x_ + y_ * y_);

    return norm_;
  }

  [[nodiscard]] Vec2 normalized() {
    float n = norm();
    return {x_ / n, y_ / n};
  }

  [[nodiscard]] Vec2 pow(float e) const {
    return {std::pow(x_, e), std::pow(y_, e)};
  }

  [[nodiscard]] Vec2 clamped(float low, float high) const {
    return {std::clamp(x_, low, high), std::clamp(y_, low, high)};
  }

  [[nodiscard]] Vec2 majored(float high) const {
    return {std::min(x_, high), std::min(y_, high)};
  }

  [[nodiscard]] Vec2 minored(float low) const {
    return {std::max(x_, low), std::max(y_, low)};
  }

  [[nodiscard]] T x() const { return x_; }
  [[nodiscard]] T y() const { return y_; }

private:
  float norm_ = -1.0f;
  T x_{}, y_{};
};

class Vec3 {
public:
  Vec3() = default;
  Vec3(const T x, const T y, const T z) : x_(x), y_(y), z_(z) {}

  friend std::ostream &operator<<(std::ostream &out, const Vec3 &p) {
    out << "{" << p.x_ << "; " << p.y_ << "; " << p.z_ << "}";
    return out;
  }

  Vec3 operator*(const T &l) const { return {x_ * l, y_ * l, z_ * l}; }

  Vec3 operator*(const Vec3 &v) const {
    return {x_ * v.x_, y_ * v.y_, z_ * v.z_};
  }

  Vec3 operator+(const Vec3 &v) const {
    return {x_ + v.x_, y_ + v.y_, z_ + v.z_};
  }

  Vec3 operator+(const float t) const { return {x_ + t, y_ + t, z_ + t}; }

  Vec3 operator-(const Vec3 &v) const {
    return {x_ - v.x_, y_ - v.y_, z_ - v.z_};
  }

  bool operator==(const Vec3 &v) {
    return x_ == v.x_ && y_ == v.y_ && z_ == v.z_;
  }
  bool operator!=(const Vec3 &v) {
    return x_ != v.x_ || y_ != v.y_ || z_ != v.z_;
  }

  void operator+=(const Vec3 &v) {
    x_ += v.x_;
    y_ += v.y_;
    z_ += v.z_;
  }

  Vec3 operator-() const { return {-x_, -y_, -z_}; }

  [[nodiscard]] T dot(const Vec3 &v) const {
    return x_ * v.x_ + y_ * v.y_ + z_ * v.z_;
  }
  [[nodiscard]] T sum() const { return x_ + y_ + z_; }

  [[nodiscard]] Vec3 cross(const Vec3 &v) const {
    return {y_ * v.z_ - z_ * v.y_, x_ * v.z_ - z_ * v.x_,
            x_ * v.y_ - y_ * v.x_};
  }

  [[nodiscard]] Vec3 pow(float e) const {
    return {std::pow(x_, e), std::pow(y_, e), std::pow(z_, e)};
  }

  [[nodiscard]] float norm() {
    if (norm_ < 0.0f)
      norm_ = std::sqrt(x_ * x_ + y_ * y_ + z_ * z_);

    return norm_;
  }

  [[nodiscard]] Vec3 normalized() {
    float n = norm();
    return {x_ / n, y_ / n, z_ / n};
  }

  [[nodiscard]] Vec3 clamped(float low, float high) const {
    return {std::clamp(x_, low, high), std::clamp(y_, low, high),
            std::clamp(z_, low, high)};
  }

  [[nodiscard]] Vec3 majored(float high) const {
    return {std::min(x_, high), std::min(y_, high), std::min(z_, high)};
  }

  [[nodiscard]] Vec3 minored(float low) const {
    return {std::max(x_, low), std::max(y_, low), std::max(z_, low)};
  }

  [[nodiscard]] T x() const { return x_; }
  [[nodiscard]] T y() const { return y_; }
  [[nodiscard]] T z() const { return z_; }

private:
  float norm_ = -1.0f;
  T x_{}, y_{}, z_{};
};

inline Vec3 operator*(float f, const Vec3 &v) { return v * f; }

struct Ray {
  Vec3 origin;
  Vec3 direction;
};
