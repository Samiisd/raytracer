//
// Created by ultra on 2/14/20.
//

#pragma once

#include "image.h"
#include "ray.h"

class Camera {
public:
  Vector3 center; // center of the camera
  Vector3 focus; // point "focused" by the camera
  Vector3 top; // normalized vector directed to the top of the camera

  float dofX; // depth of field on X
  float dofY;
protected:
};
