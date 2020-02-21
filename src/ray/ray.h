#pragma once

#include <algorithm>
#include <cmath>
#include <iostream>
#include <optional>

using T = float;

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

  [[nodiscard]] T dot(const Vec2 &v) const { return x_ * v.x_ + y_ * v.y_; }

  [[nodiscard]] Vec2 normalized() {
    if (!norm_.has_value())
      norm_ = std::sqrt(x_ * x_ + y_ * y_);

    float norm = *norm_;
    return {x_ / norm, y_ / norm};
  }

  [[nodiscard]] Vec2 clamped(float low, float high) {
    return {std::clamp(x_, low, high), std::clamp(y_, low, high)};
  }

  [[nodiscard]] Vec2 majored(float high) {
    return {std::max(x_, high), std::max(y_, high)};
  }

  [[nodiscard]] Vec2 minored(float low) {
    return {std::max(x_, low), std::max(y_, low)};
  }

  [[nodiscard]] T x() const { return x_; }
  [[nodiscard]] T y() const { return y_; }

private:
  std::optional<float> norm_;
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

  Vec3 operator-(const Vec3 &v) const {
    return {x_ - v.x_, y_ - v.y_, z_ - v.z_};
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

  [[nodiscard]] Vec3 clamped(float low, float high) {
    return {std::clamp(x_, low, high), std::clamp(y_, low, high),
            std::clamp(z_, low, high)};
  }

  [[nodiscard]] Vec3 majored(float high) {
    return {std::max(x_, high), std::max(y_, high), std::max(z_, high)};
  }

  [[nodiscard]] Vec3 minored(float low) {
    return {std::max(x_, low), std::max(y_, low), std::max(z_, low)};
  }

  [[nodiscard]] T x() const { return x_; }
  [[nodiscard]] T y() const { return y_; }
  [[nodiscard]] T z() const { return z_; }

private:
  std::optional<float> norm_;
  T x_{}, y_{}, z_{};
};

inline Vec3 operator*(float f, const Vec3 &v) { return v * f; }

struct Ray {
  Vec3 origin;
  Vec3 direction;
};
