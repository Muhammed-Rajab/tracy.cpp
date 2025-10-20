#include "materials/dielectric.hpp"
#include "ray.hpp"
#include "vec3.hpp"

Dielectric::Dielectric(double refraction_index)
    : refraction_index(refraction_index) {}

bool Dielectric::scatter(const Ray &r_in, const HitRecord &rec,
                         Color &attenuation, Ray &scattered) const {
  attenuation = Color(1.0, 1.0, 1.0);
  double ri = rec.front_face ? (1.0 / refraction_index) : refraction_index;

  Vec3 unit_direction = unit_vector(r_in.direction());
  Vec3 refracted = refract(unit_direction, rec.normal, ri);

  scattered = Ray(rec.p, refracted);
  return true;
}

double Dielectric::reflectance(double cosine, double refraction_index) {}
