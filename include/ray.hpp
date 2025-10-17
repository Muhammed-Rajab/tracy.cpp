#pragma once

#include "vec3.hpp"

class Ray {
public:
  Ray(const Point3 &origin, const Vec3 &direction);

  Point3 at(double t) const;
  const Point3 &origin() const { return orig; }
  const Vec3 &direction() const { return dir; }

private:
  Point3 orig;
  Vec3 dir;
};
