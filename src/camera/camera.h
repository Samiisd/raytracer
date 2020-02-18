//
// Created by ultra on 2/14/20.
//

#pragma once

#include <cmath>

#include "image.h"
#include "ray.h"

using crV3 = const Vector3 &;

class Camera {
public:
  Camera(const float imHeight, const float imWidth, crV3 center, crV3 focus,
         crV3 up, float focal, float fovX, float fovY)
      : eye(center),
        fov(Vector3(focal * std::tan(fovX), focal * std::tan(fovY), focal)),
        up(up), forward((focus - center).normalized()), left(forward.cross(up)),
        C(center + focal * forward), L(C + left * fov.x - up * fov.y),
        scaleY(2.0f * fov.y / imHeight), scaleX(2.0f * fov.x / imWidth) {}

  Vector3 pixelToRay(float y, float x) const;

  const Vector3 eye;

  const Vector3 fov;

  const Vector3 up, forward, left; // unary directional vectors

  const Vector3 C, L; // Center pixel and Bottom Left pixel in world coordinates

  const float scaleY, scaleX;
};
