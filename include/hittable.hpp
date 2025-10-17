#pragma once

#include "ray.hpp"
#include "vec3.hpp"
class HitRecord {
public:
  Point3 p;    // where we found the hit
  double t;    // the value of 't' for which the ray hit
  Vec3 normal; // the normal at the point of hit
};

class Hittable {

public:
  virtual ~Hittable() = default;

  virtual bool hit(const Ray &r, interval ray_t, HitRecord &rec) const = 0;
};
