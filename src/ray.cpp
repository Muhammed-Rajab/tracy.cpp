#include "ray.hpp"

// constructor
Ray::Ray() {}
Ray::Ray(const Point3 &origin, const Vec3 &direction)
    : orig(origin), dir(direction) {}

// linearly interpolates the ray and give a point at 't'
Point3 Ray::at(double t) const { return orig + dir * t; }
