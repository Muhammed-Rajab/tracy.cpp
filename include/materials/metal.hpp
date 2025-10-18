#pragma once

#include "base/material.hpp"
#include "image_writer.hpp"

class Metal : public Material {
public:
  Metal(const Color &albedo, double fuzz);

  bool scatter(const Ray &r, const HitRecord &rec, Color &attenuation,
               Ray &scattered) const override;

private:
  Color albedo;
  double fuzz;
};
