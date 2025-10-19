#pragma once

#include "base/material.hpp"
#include "image_writer.hpp"

class Dielectric : public Material {
public:
  Dielectric(double refractive_index);

  bool scatter(const Ray &r, const HitRecord &rec, Color &attenuation,
               Ray &scattered) const override;

private:
  double refractive_index;
};
