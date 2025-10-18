#pragma once

#include "base/hittable.hpp"
#include <memory>
#include <vector>

class HittableList : public Hittable {

private:
  std::vector<std::shared_ptr<Hittable>> objects;

public:
  HittableList();
  HittableList(std::shared_ptr<Hittable> object);

  void add(std::shared_ptr<Hittable> object);
  void clear();

  bool hit(const Ray &r, Interval ray_t, HitRecord &rec) const override;
};
