// Copyright 2022 UNN-CS
#include "tasks.h"

#include "circle.h"

namespace {

constexpr double kMetersInKilometer = 1000.0;
constexpr double kEarthRadiusKilometers = 6378.1;
constexpr double kInsertedRopeMeters = 1.0;
constexpr double kPoolRadius = 3.0;
constexpr double kPathWidth = 1.0;
constexpr double kConcretePricePerSquareMeter = 1000.0;
constexpr double kFencePricePerMeter = 2000.0;

double earthRadiusInMeters() {
  return kEarthRadiusKilometers * kMetersInKilometer;
}

}  // namespace

double solveEarthRopeTask() {
  const double base_radius = earthRadiusInMeters();
  Circle rope(base_radius);

  const double tight_length = rope.getFerence();
  rope.setFerence(tight_length + kInsertedRopeMeters);

  return rope.getRadius() - base_radius;
}

PoolCosts solvePoolTask() {
  Circle pool(kPoolRadius);
  Circle pool_with_path(kPoolRadius + kPathWidth);

  const double walkway_area = pool_with_path.getArea() - pool.getArea();
  const double concrete_cost = walkway_area * kConcretePricePerSquareMeter;
  const double fence_cost = pool_with_path.getFerence() * kFencePricePerMeter;

  return {concrete_cost, fence_cost};
}
