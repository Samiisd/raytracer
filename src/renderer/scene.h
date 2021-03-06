#pragma once

#include <camera.h>
#include <light.h>
#include <memory>
#include <object.h>
#include <ray.h>
#include <utility>
#include <vector>

using ObjList = std::vector<Object *>;
using LightList = std::vector<Light *>;

struct Scene {
  explicit Scene(const Camera &camera) : camera(camera) {}
  explicit Scene(const Camera &camera, ObjList objects, LightList lights)
      : camera(camera), objects(std::move(objects)), lights(std::move(lights)) {
  }

  Camera camera;
  ObjList objects;
  LightList lights;
};
