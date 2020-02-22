//
// Created by ultra on 2/14/20.
//

#include "camera.h"

Vec3 Camera::pixelToWorld(float y, float x) const {
  return L_ - ((y * scaleY_) * up_ + (x * scaleX_) * left_);
}

Camera::Camera(float imHeight, float imWidth, const Vec3 eye, const Vec3 focus,
               Vec3 up, float focal, float fov, float aspectRatio) {
  eye_ = eye;

  up_ = up.normalized();
  forward_ = (focus - eye).normalized();
  left_ = forward_.cross(up_);

  // convert degree FOV in radians
  fov = fov * static_cast<float>(M_PI / 180.0);

  float H = 2.0f * focal * std::tan(fov/2.0f);
  float W = H * aspectRatio;

  C_ = eye + focal * forward_;
  L_ = C_ + (up_ * 0.5f * H) + (left_ * 0.5f * W);

  scaleY_ = H / imHeight;
  scaleX_ = W / imWidth;
}
