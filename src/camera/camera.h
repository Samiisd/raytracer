#pragma once

#include <cmath>

#include "image.h"
#include "ray.h"

class Camera {
public:
  Camera(float imHeight, float imWidth, Vec3 eye, Vec3 focus, Vec3 up,
         float focal, float fov, float aspectRatio);

  [[nodiscard]] Vec3 pixelToWorld(float y, float x) const;

  [[nodiscard]] const Vec3 &eye() const { return eye_; };

private:
  Vec3 eye_;

  Vec3 up_, forward_, left_; // unary directional vectors
  Vec3 C_, L_; // Center pixel and Bottom Left pixel in world coordinates
  float scaleY_, scaleX_;
};
