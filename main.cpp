#include "vec3.hpp"
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

#include "include/image_writer.hpp"

int main() {

  int width = 256;
  int height = 256;
  int channels = 3;

  auto framebuffer = std::vector<Vec3>(width * height);
  for (int j = 0; j < height; j += 1) {
    for (int i = 0; i < width; i += 1) {
      std::size_t idx = j * width + i;
      double x = (double)i / (double)width;
      double y = (double)j / (double)height;
      double z = (double)(i * j) / (double)(width * height);
      Vec3 pixel = {x, y, z};
      framebuffer[idx] = pixel;
    }
  }

  write_framebuffer_to_png("./image.png", framebuffer, width, height, channels);

  return 0;
}
