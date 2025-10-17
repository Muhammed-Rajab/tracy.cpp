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

  return 0;
}
