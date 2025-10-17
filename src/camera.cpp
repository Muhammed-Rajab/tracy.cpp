#include "camera.hpp"
#include "utils.hpp"
#include "vec3.hpp"
#include <cstddef>

// std::vector<Vec3> Camera::render() {
//
//   for (std::size_t j = 0; j < image_height; j += 1) {
//     for (std::size_t i = 0; i < image_width; i += 1) {
//       std::cout << i << " " << j << "\n";
//     }
//   }
//
//   return {};
// }
//

void Camera::initialize() {

  // calculate image height from aspect ratio (min height: 1)
  image_height = static_cast<int>(image_width / aspect_ratio);
  image_height = (image_height < 1) ? 1 : image_height;

  center = lookfrom;

  // calculate viewport dimensions
  auto focal_length = (lookfrom - lookat).length();
  auto theta = degrees_to_radians(vfov);
  auto h = std::tan(theta / 2) * focal_length;
  auto viewport_height = 2.0 * h;
  auto viewport_width =
      viewport_height * (static_cast<double>(image_width) / image_height);

  // calculate basis vectors of camera frame
  w = unit_vector(lookfrom - lookat);
  u = unit_vector(cross(vup, w));
  v = cross(w, u);

  // calculate vector horizontally across and vertically down viewport
  Vec3 viewport_u = viewport_width * u;
  Vec3 viewport_v = viewport_height * -v;

  // horizontal and vertical distance between two adjacent pixels
  pixel_delta_u = viewport_u / image_width;
  pixel_delta_v = viewport_v / image_height;

  // upper left pixel calculation
  auto viewport_upper_left =
      center - (focal_length * w) - viewport_u / 2 - viewport_v / 2;
  pixel00_loc = viewport_upper_left + 0.5 * pixel_delta_u + 0.5 * pixel_delta_v;
}

Ray Camera::get_ray(std::size_t i, std::size_t j) const {
  auto ray_origin = center;
  auto pixel_position = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);

  auto ray_direction = pixel_position - ray_origin;
  return Ray(ray_origin, ray_direction);
}
