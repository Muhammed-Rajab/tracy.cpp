#include "hittable_list.hpp"
#include "sphere.hpp"
#include "vec3.hpp"
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <memory>
#include <vector>

#include "include/camera.hpp"
#include "include/image_writer.hpp"

int main() {

  HittableList world;

  // sphere
  world.add(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5));

  // ground
  world.add(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100));

  Camera cam;
  cam.image_width = 256;
  cam.aspect_ratio = 16.0 / 9.0;

  auto framebuffer = cam.render(world);
  write_framebuffer_to_png("./image.png", framebuffer, cam.image_width,
                           cam.image_height, 3);

  return 0;
}
