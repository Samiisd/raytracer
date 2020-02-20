//
// Created by ultra on 2/14/20.
//

#pragma once

#include <cmath>

#include "image.h"
#include "ray.h"

using crV3 = const Vec3 &;

class Camera {
public:
  Camera(const float imHeight, const float imWidth, crV3 center, crV3 focus,
         crV3 up, float focal, float fov, float aspectRatio)
      : aspectRatio(imWidth / imHeight), eye(center),
        H(2.0f * focal * std::tan(fov / 2)),
        W(H * aspectRatio),
        up(up.normalized()), forward((focus - eye).normalized()), left(forward.cross(up)),
        C(eye + focal * forward), L(C + (left * W * 0.5f) + (up * H * 0.5f)),
        scaleY(H / imHeight), scaleX(W / imWidth) {}

  [[nodiscard]] Vec3 pixelToRay(float y, float x) const;

  const float aspectRatio;

  const Vec3 eye;

  const float H, W;

  const Vec3 up, forward, left; // unary directional vectors

  const Vec3 C, L; // Center pixel and Bottom Left pixel in world coordinates

  const float scaleY, scaleX;
};
