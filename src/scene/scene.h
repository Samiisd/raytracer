//
// Created by ultra on 2/14/20.
//

#pragma once

#include <camera.h>
#include <light.h>
#include <object.h>
#include <ray.h>
#include <vector>

struct Scene {
  Camera camera;
  std::vector<Object> objects;
  std::vector<Light> lights;
};
