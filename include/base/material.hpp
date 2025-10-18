#pragma once

#include "base/hittable.hpp"
#include "image_writer.hpp"
#include "ray.hpp"

class Material {
public:
  virtual ~Material() = default;

  // that little = 0 is important because this is an abstract class. OOP in CPP
  // is something of a separate language ong!
  virtual bool scatter(const Ray &r, const HitRecord &rec, Color &attenuation,
                       Ray &scattered) const = 0;
};
