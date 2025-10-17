#include "vec3.hpp"
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

#include "include/camera.hpp"
#include "include/image_writer.hpp"

int main() {

  Camera cam;
  cam.image_width = 256;
  cam.aspect_ratio = 16.0 / 9.0;

  auto framebuffer = cam.render();
  write_framebuffer_to_png("./image.png", framebuffer, cam.image_width,
                           cam.image_height, 3);

  return 0;
}
