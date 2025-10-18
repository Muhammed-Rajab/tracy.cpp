#pragma once

#include "interval.hpp"
#include "ray.hpp"
#include "vec3.hpp"

class HitRecord {
public:
  Point3 p; // where we found the hit
  double t; // the value of 't' for which the ray hit

  // TODO: add comments on this design choice
  bool front_face;
  Vec3 normal; // the normal at the point of hit

  void set_face_normal(const Ray &r, const Vec3 &outward_normal);
};

class Hittable {
public:
  virtual ~Hittable() = default;

  virtual bool hit(const Ray &r, Interval ray_t, HitRecord &rec) const = 0;
};
