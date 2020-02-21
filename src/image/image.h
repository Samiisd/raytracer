#pragma once

#include <cstdint>
#include <iostream>
#include <ray.h>
#include <vector>

class Image {
public:
  Image(size_t height, size_t width);

  Vec3 &operator()(size_t y, size_t x);
  const size_t height, width;

  friend std::ostream&operator<<(std::ostream& out, const Image& im);
private:
  std::vector<Vec3> _buffer;
};
