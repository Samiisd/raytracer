#include "image.h"

Image::Image(size_t height, size_t width) : height(height), width(width) {
  this->_buffer = std::vector<Vec3>(height * width);
}

Vec3 &Image::operator()(const size_t y, const size_t x) {
  return this->_buffer[y * this->width + x];
}

std::ostream &operator<<(std::ostream &out, const Image &im) {
  auto printPixel = [&out](const Vec3 &pixel) -> std::ostream & {
    out << static_cast<uint>(255.0f * pixel.x()) << ' '
        << static_cast<uint>(255.0f * pixel.y()) << ' '
        << static_cast<uint>(255.0f * pixel.z());
    return out;
  };

  out << "P3"
      << "\n"
      << im.width << "\t" << im.height << "\n"
      << 255 << "\n";

  printPixel(im._buffer.at(0)) << '\t';
  for (size_t i = 1; i < im._buffer.size(); i++) {
    printPixel(im._buffer.at(i));
    if ((i % im.width) == 0)
      out << '\n';
    else
      out << '\t';
  }

  return out;
}
