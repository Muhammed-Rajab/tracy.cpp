#include "sphere.hpp"

Sphere::Sphere(const Point3 &center, const double radius)
    : center(center), radius(std::fmax(0, radius)) {}

bool Sphere::hit(const Ray &r, Interval ray_t, HitRecord &rec) const {}
