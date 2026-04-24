// Copyright 2022 UNN-CS
#include "tasks.h"

#include "circle.h"

namespace {

constexpr double kEarthRadiusMeters = 6378.1 * 1000.0;
constexpr double kPoolRadius = 3.0;
constexpr double kPathWidth = 1.0;
constexpr double kConcretePricePerSquareMeter = 1000.0;
constexpr double kFencePricePerMeter = 2000.0;

}  // namespace

double solveEarthRopeTask() {
  Circle earth(kEarthRadiusMeters);
  const double original_ference = earth.getFerence();
  earth.setFerence(original_ference + 1.0);
  return earth.getRadius() - kEarthRadiusMeters;
}

PoolCosts solvePoolTask() {
  Circle pool(kPoolRadius);
  Circle outer(pool.getRadius() + kPathWidth);

  const double path_area = outer.getArea() - pool.getArea();
  const double concrete_cost = path_area * kConcretePricePerSquareMeter;
  const double fence_cost = outer.getFerence() * kFencePricePerMeter;

  return {concrete_cost, fence_cost};
}
