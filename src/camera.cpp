#include "camera.hpp"
#include "image_writer.hpp"
#include "utils.hpp"
#include "vec3.hpp"
#include <cstddef>
#include <vector>

std::vector<Vec3> Camera::render() {
  // makes sure every value is calculated properly
  initialize();

  std::vector<Vec3> framebuffer(image_width * image_height);

  for (std::size_t j = 0; j < image_height; j += 1) {
    for (std::size_t i = 0; i < image_width; i += 1) {

      std::size_t index = j * image_width + i;

      // get the ray
      Ray ray = get_ray(i, j);

      // trace the ray to get the color
      Color pixel_color = trace_ray(ray);

      // append it to framebuffer
      framebuffer[index] = pixel_color;
    }
  }

  return framebuffer;
}

double hit_sphere(const Ray &r, const Point3 &center, const double radius) {
  Vec3 oc = center - r.origin();
  auto a = dot(r.direction(), r.direction());
  auto b = -2.0 * dot(r.direction(), oc);
  auto c = dot(oc, oc) - radius * radius;
  auto discriminant = b * b - 4 * a * c;

  if (discriminant < 0) {
    return -1.0;
  } else {
    return (-b - std::sqrt(discriminant)) / (2.0 * a);
  }
}

Color Camera::trace_ray(const Ray &r) const {
  // check for hits
  Point3 center = Point3(0, 0, -1);
  double radius = 0.5;
  double t = hit_sphere(r, center, radius);

  if (t >= 0.0) {
    Point3 P = r.at(t);
    Vec3 N = (P - center) / radius;
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
