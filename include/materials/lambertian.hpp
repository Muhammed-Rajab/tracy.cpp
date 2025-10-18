#pragma once

#include "base/material.hpp"
#include "image_writer.hpp"

class Lambertian : public Material {
public:
  Lambertian(const Color &albedo);

  bool scatter(const Ray &r, const HitRecord &rec, Color &attenuation,
               Ray &scattered) const override;

private:
  Color albedo;
};
