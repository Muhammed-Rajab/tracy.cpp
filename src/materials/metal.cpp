#include "materials/metal.hpp"
#include "vec3.hpp"

Metal::Metal(const Color &albedo) : albedo(albedo) {}

bool Metal::scatter(const Ray &r_in, const HitRecord &rec, Color &attenuation,
                    Ray &scattered) const {
  Vec3 reflected = reflect(r_in.direction(), rec.normal);
  scattered = Ray(rec.p, reflected);
  attenuation = albedo;
  return true;
}
