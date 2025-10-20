#include "materials/metal.hpp"
#include "vec3.hpp"

Metal::Metal(const Color &albedo, double fuzz)
    : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}

bool Metal::scatter(const Ray &r_in, const HitRecord &rec, Color &attenuation,
                    Ray &scattered) const {
  Vec3 reflected = reflect(r_in.direction(), rec.normal);

  // adds the fuzz to the metal surface
  reflected = unit_vector(reflected) + (fuzz * random_unit_vector());
  scattered = Ray(rec.p, reflected);
  attenuation = albedo;
  // scattered and normal are in same direction
  return (dot(scattered.direction(), rec.normal) > 0);
}
