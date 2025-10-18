#pragma once

#include "base/hittable.hpp"
#include "image_writer.hpp"
#include "ray.hpp"

class Material {
public:
  virtual ~Material() = default;

  virtual bool scatter(const Ray &r, const HitRecord &rec, Color &attenuation,
                       Ray &scattered) const;
};
