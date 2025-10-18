#include "base/hittable.hpp"
#include "vec3.hpp"

void HitRecord::set_face_normal(const Ray &r, const Vec3 &outward_normal) {
  // r_direction dot  outward normal < 0.0 means opposite direction
  // or just from the front face.
  front_face = dot(r.direction(), outward_normal) < 0.0;
  normal = front_face ? outward_normal : -outward_normal;
}
