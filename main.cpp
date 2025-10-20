#include "hittable_list.hpp"
#include "materials/dielectric.hpp"
#include "materials/lambertian.hpp"
#include "materials/metal.hpp"
#include "sphere.hpp"
#include "vec3.hpp"
#include <memory>

#include "include/camera.hpp"
#include "include/image_writer.hpp"

int test1() {
  HittableList world;

  // spheres
  auto metal_ground = std::make_shared<Metal>(Color(1.0, .41, .7), 0.3);

  auto lambertian_red = std::make_shared<Lambertian>(Color(1.0, 0.0, 0.0));
  auto lambertian_green = std::make_shared<Lambertian>(Color(0.0, 1.0, 0.9));
  auto lambertian_blue = std::make_shared<Lambertian>(Color(0.0, 0.0, 1.0));
  auto lambertian_yellow = std::make_shared<Lambertian>(Color(1.0, 1.0, 0.0));

  auto metal_red = std::make_shared<Metal>(Color(1.0, 0.0, 0.0), .2);
  auto metal_green = std::make_shared<Metal>(Color(0.0, 1.0, 0.0), .4);
  auto metal_yellow = std::make_shared<Metal>(Color(1.0, 1.0, 0.0), .6);

  auto metal_silver = std::make_shared<Metal>(Color(.8, .8, .8), .05);

  auto metal_blue = std::make_shared<Metal>(Color(0.0, 0.0, 1.0), .8);

  auto dielectric = std::make_shared<Dielectric>(1.5);

  world.add(std::make_shared<Sphere>(Point3(-1, 0, -1), 0.5, dielectric));
  world.add(std::make_shared<Sphere>(Point3(0.0, 0, -1), 0.5, metal_silver));
  world.add(std::make_shared<Sphere>(Point3(1, 0, -1), 0.5, metal_green));

  // ground, which is also huge sphere (checkmate, flath earther!)
  world.add(
      std::make_shared<Sphere>(Point3(0, -2000.5, -1), 2000, metal_ground));

  // auto material_ground = make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
  // auto material_center = make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
  // auto material_left = make_shared<Metal>(Color(0.8, 0.8, 0.8));
  // auto material_right = make_shared<Metal>(Color(0.8, 0.6, 0.2));
  //
  // world.add(
  //     make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0,
  //     material_ground));
  // world.add(make_shared<Sphere>(Point3(0.0, 0.0, -1.2), 0.5,
  // material_center)); world.add(make_shared<Sphere>(Point3(-1.0, 0.0, -1.0),
  // 0.5, material_left)); world.add(make_shared<Sphere>(Point3(1.0, 0.0, -1.0),
  // 0.5, material_right));

  Camera cam;
  cam.samples_per_pixel = 10;
  cam.image_width = 400;
  cam.max_depth = 20;
  cam.aspect_ratio = 16.0 / 9.0;

  auto framebuffer = cam.render(world);
  write_framebuffer_to_png("./image.png", framebuffer, cam.image_width,
                           cam.image_height, 3);

  return 0;
}

int test2() {
  HittableList world;

  auto material_ground = make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
  auto material_center = make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
  auto material_left = make_shared<Dielectric>(1.00 / 1.33);
  auto material_right = make_shared<Metal>(Color(0.8, 0.6, 0.2), 0.0);

  world.add(
      make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, material_ground));
  world.add(make_shared<Sphere>(Point3(0.0, 0.0, -1.2), 0.5, material_center));
  world.add(make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, material_left));
  world.add(make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, material_right));

  Camera cam;
  cam.samples_per_pixel = 20;
  cam.image_width = 400;
  cam.max_depth = 50;
  cam.aspect_ratio = 16.0 / 9.0;

  auto framebuffer = cam.render(world);
  write_framebuffer_to_png("./image.png", framebuffer, cam.image_width,
                           cam.image_height, 3);

  return 0;
}

int main() {

  // test1();
  test2();
  return 0;
}
