#pragma once

#include "image_writer.hpp"
#include "ray.hpp"
#include "vec3.hpp"

#include <cstddef>
#include <vector>

class Camera {

public:
  double aspect_ratio = 1.0; // generated image's aspect ratio
  std::size_t image_width = 100;

  // WARN: This shouldn't be set from outside. this is to be calculated inside
  // intialize method.
  std::size_t
      image_height; // computed height of the image from width and aspect ratio
  double vfov = 90; // vertical field of view
  Point3 lookfrom = Point3(0, 0, 0); // 'eye point'
  Point3 lookat = Point3(0, 0, -1);  // where to look at
  Vec3 vup = Vec3(0, 1, 0);          // up direction of the camera

  std::vector<Vec3> render();

private:
  Point3 center;      // 'eye point'
  Point3 pixel00_loc; // location of the first pixel
  Vec3 pixel_delta_u; // horizontal vector between two adjacent pixels
  Vec3 pixel_delta_v; // vertical vector between two adjacent pixels
  Vec3 u, v, w;       // basis vectors of camera frame

  void initialize(); // calculates important figures

  Ray get_ray(std::size_t i, std::size_t j) const; // gets ray for a given pixel

  Color trace_ray(const Ray &r) const; // trace the ray to get color
};
