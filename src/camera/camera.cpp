//
// Created by ultra on 2/14/20.
//

#include "camera.h"

Vector3 Camera::pixelToRay(float y, float x) {
  return (fov * Vector3{x, y, 1} - center).normalized();
}
