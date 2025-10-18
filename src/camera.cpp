#include "camera.hpp"
#include "base/hittable.hpp"
#include "hittable_list.hpp"
#include "image_writer.hpp"
#include "interval.hpp"
#include "utils.hpp"
#include "vec3.hpp"
#include <cstddef>
#include <vector>

std::vector<Vec3> Camera::render(const HittableList &world) {
  // makes sure every value is calculated properly
  initialize();

  std::vector<Vec3> framebuffer(image_width * image_height);

  for (std::size_t j = 0; j < image_height; j += 1) {
    std::clog << "line #" << j + 1 << " out of " << image_height << "\n"
              << std::flush;
    for (std::size_t i = 0; i < image_width; i += 1) {

      std::size_t index = j * image_width + i;
      Color pixel_color(0, 0, 0);

      for (std::size_t sample = 0; sample < samples_per_pixel; sample += 1) {
        Ray ray = get_ray(i, j);

        pixel_color += trace_ray(ray, world);
      }

      framebuffer[index] = pixel_color * inv_samples_per_pix;
    }
  }

  std::clog << "Done. \n";

  return framebuffer;
}

Color Camera::trace_ray(const Ray &r, const HittableList &world) const {
  HitRecord rec;

  if (world.hit(r, Interval(0.001, infinity), rec)) {
    auto N = rec.normal;
    return 0.5 * Color(N.x() + 1, N.y() + 1, N.z() + 1);
  }

  // gradient from up to down
  double a = 0.5 * (unit_vector(r.direction()).y() + 1.0);

  Color gradient_start_color = Color(0.96, 0.94, 0.94);
  Color gradient_end_color = Color(0.99, 0.73, 0.17);

  return (1.0 - a) * gradient_start_color + a * gradient_end_color;
}

void Camera::initialize() {

  // calculate image height from aspect ratio (min height: 1)
  image_height = static_cast<int>(image_width / aspect_ratio);
  image_height = (image_height < 1) ? 1 : image_height;

  // for scaling colors
  inv_samples_per_pix = 1.0 / samples_per_pixel;

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
  auto offset = sample_square();
  auto pixel_sample = pixel00_loc + ((i + offset.x()) * pixel_delta_u) +
                      ((j + offset.y()) * pixel_delta_v);

  auto ray_origin = center;
  auto ray_direction = pixel_sample - ray_origin;
  return Ray(ray_origin, ray_direction);
}

Vec3 Camera::sample_square() const {
  return Vec3(random_double() - 0.5, random_double() - 0.5, 0);
}
