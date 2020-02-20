//
// Created by ultra on 2/14/20.
//

#include "image.h"

Image::Image(size_t height, size_t width): height(height), width(width) {
  this->_buffer = std::vector<Color>(height * width);
}

Color &Image::operator()(const size_t y, const size_t x) {
  return this->_buffer[y * this->width + x];
}

std::ostream &operator<<(std::ostream &out, const Image &im) {
  out << "P3" << "\n"
  << im.width << "\t" << im.height << "\n"
  << static_cast<unsigned >(uint_fast8_t(-1)) << "\n";

  out << im._buffer.at(0) << '\t';
  for (size_t i = 1; i < im._buffer.size(); i++) {
    out << im._buffer.at(i);
    if ((i % im.width) == 0)
      out << '\n';
    else
      out << '\t';
  }

  return out;
}
