#pragma once

#include <cmath>

#include "ray.h"
#include "texture.h"

class Camera {
public:
  Camera(float imHeight, float imWidth, const Vec3 eye, const Vec3 focus,
         Vec3 up, float focal, float fov, float aspectRatio) {
    eye_ = eye;

    up_ = up.normalized();
    forward_ = (focus - eye).normalized();
    left_ = forward_.cross(up_);

    // convert degree FOV in radians
    fov = fov * static_cast<float>(M_PI / 180.0);

    float H = 2.0f * focal * std::tan(fov / 2.0f);
    float W = H * aspectRatio;

    C_ = eye + focal * forward_;
    L_ = C_ + (up_ * 0.5f * H) + (left_ * 0.5f * W);

    scaleY_ = H / imHeight;
    scaleX_ = W / imWidth;
  }
  [[nodiscard]] inline Vec3 pixelToWorld(float y, float x) const {
    return L_ - ((y * scaleY_) * up_ + (x * scaleX_) * left_);
  }

  [[nodiscard]] const Vec3 &eye() const { return eye_; };

private:
  Vec3 eye_;

  Vec3 up_, forward_, left_; // unary directional vectors
  Vec3 C_, L_; // Center pixel and Bottom Left pixel in world coordinates
  float scaleY_, scaleX_;
};
