#pragma once

#include <camera.h>
#include <light.h>
#include <object.h>
#include <ray.h>
#include <vector>
#include <memory>

struct Scene {
  explicit Scene(const Camera& camera) : camera(camera) {}

  Camera camera;
  std::vector<std::shared_ptr<Object>> objects;
  std::vector<std::shared_ptr<Light>> lights;
};
