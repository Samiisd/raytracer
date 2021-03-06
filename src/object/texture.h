//
// Created by ultra on 2/14/20.
//

#pragma once

#include "ray.h"
#include "texture.h"

class TextureMaterial {
public:
  virtual ~TextureMaterial() = default;

  // Returns the color at y,x
  [[nodiscard]] virtual Vec3 colorAt(const Vec2 &uv) const = 0;

  // Returns the Ambient reflection coefficient at (y,x)
  [[nodiscard]] virtual float kaAt(const Vec2 &uv) const = 0;

  // Returns the Diffuse reflection coefficient at (y,x)
  [[nodiscard]] virtual float kdAt(const Vec2 &uv) const = 0;

  // Returns the Specular reflection coefficient at (y,x)
  [[nodiscard]] virtual float ksAt(const Vec2 &uv) const = 0;

  // Returns the Phong ns coefficient at (y,x)
  [[nodiscard]] virtual float nsAt(const Vec2 &uv) const = 0;

  // Returns the refractive index at (y,x)
  [[nodiscard]] virtual float refractiveIndexAt(const Vec2 &uv) const = 0;

  // Returns the reflectivity of the material
  [[nodiscard]] virtual float reflectivityAt(const Vec2 &uv) const = 0;

protected:
};

class UniformTexture : public TextureMaterial {
public:
  UniformTexture(const Vec3 color, float kd, float ks, float ka, float ns,
                 float ri, float reflectivity = 0.10)
      : color_(color), kd_(kd), ks_(ks), ka_(ka), ns_(ns), ri_(ri),
        reflectivity_(reflectivity) {}

  [[nodiscard]] Vec3 colorAt(const Vec2 &) const final { return color_; }
  [[nodiscard]] float kaAt(const Vec2 &) const final { return ka_; }
  [[nodiscard]] float kdAt(const Vec2 &) const final { return kd_; }
  [[nodiscard]] float ksAt(const Vec2 &) const final { return ks_; }
  [[nodiscard]] float nsAt(const Vec2 &) const final { return ns_; }
  [[nodiscard]] float refractiveIndexAt(const Vec2 &) const final {
    return ri_;
  }
  [[nodiscard]] float reflectivityAt(const Vec2 &uv) const final {
    return reflectivity_;
  };

private:
  const Vec3 color_;
  const float kd_;
  const float ks_;
  const float ka_;
  const float ns_;
  const float ri_;
  const float reflectivity_;
};
