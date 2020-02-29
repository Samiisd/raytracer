#pragma once

#include <cstdint>
#include <iostream>
#include <ray.h>
#include <vector>

class Image {
public:
  Image(size_t height, size_t width);
  ~Image();

  Vec3 &operator()(size_t y, size_t x);
  Vec3 &operator[](size_t i);

  const size_t height, width;

  friend std::ostream&operator<<(std::ostream& out, const Image& im);
private:
  Vec3 *_buffer;
};
