#include "materials/lambertian.hpp"
#include "vec3.hpp"

Lambertian::Lambertian(const Color &albedo) : albedo(albedo) {}

bool Lambertian::scatter(const Ray &r, const HitRecord &rec, Color &attenuation,
                         Ray &scattered) const {
  // TODO: switch between two to see the difference between lambertian
  // distribution and uniform distribution on hemisphere.
  Vec3 scatter_direction = rec.normal + random_unit_vector();
  // Vec3 scatter_direction = random_unit_vector_on_hemisphere(rec.normal);

  // make sure the vector isn't super small
  if (scatter_direction.near_zero())
    scatter_direction = rec.normal;

  scattered = Ray(rec.p, scatter_direction);
  attenuation = albedo;
  return true;
}
