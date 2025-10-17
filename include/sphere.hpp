#pragma once

#include "base/hittable.hpp"
#include "vec3.hpp"

class Sphere : public Hittable {

public:
  Sphere(const Point3 &center, const double radius);

  bool hit(const Ray &r, Interval ray_t, HitRecord &rec) const;

private:
  Point3 center;
  double radius;
};
