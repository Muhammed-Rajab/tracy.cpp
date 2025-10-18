#include "base/material.hpp"
#include "hittable_list.hpp"
#include "materials/lambertian.hpp"
#include "materials/metal.hpp"
#include "sphere.hpp"
#include "vec3.hpp"
#include <memory>

#include "include/camera.hpp"
#include "include/image_writer.hpp"

int main() {

  HittableList world;

  // spheres
  auto lambertian_red = std::make_shared<Lambertian>(Color(1.0, 0.0, 0.0));
  auto lambertian_green = std::make_shared<Lambertian>(Color(0.0, 1.0, 0.0));
  auto lambertian_blue = std::make_shared<Lambertian>(Color(0.0, 0.0, 1.0));
  auto lambertian_yellow = std::make_shared<Lambertian>(Color(1.0, 1.0, 0.0));

  auto metal_red = std::make_shared<Metal>(Color(1.0, 0.0, 0.0));
  auto metal_green = std::make_shared<Metal>(Color(0.0, 1.0, 0.0));
  auto metal_yellow = std::make_shared<Metal>(Color(1.0, 1.0, 0.0));

  world.add(std::make_shared<Sphere>(Point3(-1, 0, -1), 0.5, metal_red));
  world.add(std::make_shared<Sphere>(Point3(0.0, 0, -1), 0.5, metal_yellow));
  world.add(std::make_shared<Sphere>(Point3(1, 0, -1), 0.5, metal_green));

  // ground, which is also huge sphere (checkmate, flath earther!)
  world.add(
      std::make_shared<Sphere>(Point3(0, -2000.5, -1), 2000, lambertian_blue));

  Camera cam;
  cam.samples_per_pixel = 50;
  cam.image_width = 400;
  cam.max_depth = 20;
  cam.aspect_ratio = 16.0 / 9.0;

  auto framebuffer = cam.render(world);
  write_framebuffer_to_png("./image.png", framebuffer, cam.image_width,
                           cam.image_height, 3);

  return 0;
}
