//
// Created by ultra on 2/14/20.
//

#include "camera.h"

Vector3 Camera::pixelToRay(float y, float x) const {
  return L - ((y * scaleY) * up + (x * scaleX) * left);
}
