#include <iostream>
#include <vector.h>
#include <image.h>


int main() {
  const size_t image_height = 400, image_width = 400;
  Image result(image_height, image_width);

  for (size_t y = 0; y < image_height; y++)
    for (size_t x = 0; x < image_width; x++) {
      uint_fast8_t p = ((x % 20) == 0 || (y % 15) == 0) * (uint_fast8_t)(-1);
      result(y, x) = Pixel{p, p, p};
    }

  const Vector3<float> a{1,2,3};
  const Vector3<float> b{5,7,8};

  std::cout << result << std::endl;

//  std::cout << a << '+' << b << '=' << a + b << std::endl;
  return 0;
}
