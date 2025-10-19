#include "materials/dielectric.hpp"
#include "vec3.hpp"

Dielectric::Dielectric(double refraction_index)
    : refraction_index(refraction_index) {}

bool Dielectric::scatter(const Ray &r_in, const HitRecord &rec,
                         Color &attenuation, Ray &scattered) const {
  return false;
}

double Dielectric::reflectance(double cosine, double refraction_index) {}
