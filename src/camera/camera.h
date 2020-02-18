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
  Camera(crV3 center, crV3 focus, crV3 top, float focal, float fovX, float fovY)
      : center(center), focus(focus), top(top), focal(focal), fovX(fovX),
        fovY(fovY),
        fov(Vector3(focal / std::cos(fovX), focal / std::cos(fovY), focal)) {}

  Vector3 pixelToRay(float y, float x);

  Vector3 center; // center of the camera
  Vector3 focus;  // point "focused" by the camera
  Vector3 top;    // normalized vector directed to the top of the camera

  const float focal; // position of the image plan on the Z-axis

  const float fovX; // field of view on X
  const float fovY;

  const Vector3 fov;
};
