#include "materials/dielectric.hpp"
#include "vec3.hpp"

Dielectric::Dielectric(double refractive_index)
    : refractive_index(refractive_index) {}

bool Dielectric::scatter(const Ray &r_in, const HitRecord &rec,
                         Color &attenuation, Ray &scattered) const {
  attenuation = Color(1.0, 1.0, 1.0); // no attenuation happens
  double ri = rec.front_face ? (1.0 / refractive_index) : refractive_index;

  Vec3 unit_direction = unit_vector(r_in.direction());
  double cos_theta = std::fmin(dot(-unit_direction, rec.normal), 1.0);
  double sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);

  Vec3 direction;

  if (ri * sin_theta > 1.0) {
    // have to reflect
    direction = reflect(unit_direction, rec.normal);
  } else {
    // can refract
    direction = refract(unit_direction, rec.normal, ri);
  }

  scattered = Ray(rec.p, direction);
  return true;
}
