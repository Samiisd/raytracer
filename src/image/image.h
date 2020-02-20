//
// Created by ultra on 2/14/20.
//

#ifndef RAYTRACER_IMAGE_H
#define RAYTRACER_IMAGE_H

#include <cstdint>
#include <vector>
#include <iostream>

struct Color {
    uint_fast8_t r, g, b;

    friend std::ostream&operator<<(std::ostream& out, const Color & p) {
        out << static_cast<unsigned>(p.r) << " " << static_cast<unsigned>(p.g) << " " << static_cast<unsigned>(p.b);
        return out;
    }
};

class Image {
public:
  Image(size_t height, size_t width);

  Color &operator()(size_t y, size_t x);
  const size_t height, width;

  friend std::ostream&operator<<(std::ostream& out, const Image& im);
private:
  std::vector<Color> _buffer;
};

#endif // RAYTRACER_IMAGE_H
