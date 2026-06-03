// Copyright 2025 UNN-CS Team

#include <gtest/gtest.h>

#include <cmath>
#include <stdexcept>

#include "circle.h"
#include "tasks.h"

namespace {

constexpr double kPi = 3.14159265358979323846;
constexpr double kTolerance = 1e-6;

double circumferenceByRadius(double radius) {
  return 2.0 * kPi * radius;
}

double areaByRadius(double radius) {
  return kPi * radius * radius;
}

void expectCircleState(const Circle& circle, double radius,
                       double tolerance = kTolerance) {
  EXPECT_NEAR(circle.getRadius(), radius, tolerance);
  EXPECT_NEAR(circle.getFerence(), circumferenceByRadius(radius), tolerance);
  EXPECT_NEAR(circle.getArea(), areaByRadius(radius), tolerance);
}

}  // namespace

TEST(CircleConstructor, CreatesZeroCircleByDefault) {
  const Circle circle;
  expectCircleState(circle, 0.0);
}

TEST(CircleConstructor, BuildsAllValuesFromRadius) {
  const Circle circle(7.25);
  expectCircleState(circle, 7.25);
}

TEST(CircleConstructor, AcceptsExplicitZeroRadius) {
  const Circle circle(0.0);
  expectCircleState(circle, 0.0);
}

TEST(CircleConstructor, RejectsNegativeRadius) {
  EXPECT_THROW(Circle(-0.01), std::invalid_argument);
}

TEST(CircleRadiusSetter, RecalculatesCircumferenceAndArea) {
  Circle circle(1.0);
  circle.setRadius(4.5);
  expectCircleState(circle, 4.5);
}

TEST(CircleRadiusSetter, CanCollapseCircleToPoint) {
  Circle circle(9.0);
  circle.setRadius(0.0);
  expectCircleState(circle, 0.0);
}

TEST(CircleRadiusSetter, KeepsPreviousStateAfterInvalidInput) {
  Circle circle(3.2);

  EXPECT_THROW(circle.setRadius(-5.0), std::invalid_argument);

  expectCircleState(circle, 3.2);
}

TEST(CircleFerenceSetter, RecalculatesRadiusAndArea) {
  Circle circle;
  const double length = 31.41592653589793;

  circle.setFerence(length);

  expectCircleState(circle, 5.0);
}

TEST(CircleFerenceSetter, HandlesZeroCircumference) {
  Circle circle(2.5);
  circle.setFerence(0.0);
  expectCircleState(circle, 0.0);
}

TEST(CircleFerenceSetter, KeepsPreviousStateAfterInvalidInput) {
  Circle circle(6.0);

  EXPECT_THROW(circle.setFerence(-1.0), std::invalid_argument);

  expectCircleState(circle, 6.0);
}

TEST(CircleAreaSetter, RecalculatesRadiusAndCircumference) {
  Circle circle(1.0);
  const double target_radius = 8.0;

  circle.setArea(areaByRadius(target_radius));

  expectCircleState(circle, target_radius);
}

TEST(CircleAreaSetter, HandlesZeroArea) {
  Circle circle(12.0);
  circle.setArea(0.0);
  expectCircleState(circle, 0.0);
}

TEST(CircleAreaSetter, KeepsPreviousStateAfterInvalidInput) {
  Circle circle(2.75);

  EXPECT_THROW(circle.setArea(-100.0), std::invalid_argument);

  expectCircleState(circle, 2.75);
}

TEST(CircleGetters, WorkForConstObject) {
  const Circle circle(10.0);

  EXPECT_NEAR(circle.getRadius(), 10.0, kTolerance);
  EXPECT_NEAR(circle.getFerence(), circumferenceByRadius(10.0), kTolerance);
  EXPECT_NEAR(circle.getArea(), areaByRadius(10.0), kTolerance);
}

TEST(CircleConsistency, RadiusAndAreaStayMathematicallyLinked) {
  Circle circle(5.5);

  EXPECT_NEAR(circle.getArea() / circle.getRadius(),
              0.5 * circle.getFerence(), kTolerance);
}

TEST(CircleConsistency, ConsecutiveDifferentSettersUseTheNewestValue) {
  Circle circle(4.0);

  circle.setRadius(2.0);
  circle.setFerence(circumferenceByRadius(3.0));
  circle.setArea(areaByRadius(6.0));

  expectCircleState(circle, 6.0);
}

TEST(CircleConsistency, LargeRadiusDoesNotLosePracticalPrecision) {
  const Circle circle(6378100.0);

  EXPECT_NEAR(circle.getFerence(), circumferenceByRadius(6378100.0), 1e-3);
  EXPECT_NEAR(circle.getArea(), areaByRadius(6378100.0), 1e4);
}

TEST(EarthRopeTask, GapIsPositive) {
  EXPECT_GT(solveEarthRopeTask(), 0.0);
}

TEST(EarthRopeTask, GapDoesNotDependOnEarthRadiusFormula) {
  EXPECT_NEAR(solveEarthRopeTask(), 1.0 / (2.0 * kPi), kTolerance);
}

TEST(EarthRopeTask, GapRoundedToMetersMatchesKnownAnswer) {
  EXPECT_NEAR(solveEarthRopeTask(), 0.159154943, 1e-9);
}

TEST(PoolTask, ConcreteCostUsesWalkwayAreaOnly) {
  const PoolCosts costs = solvePoolTask();
  const double expected_area = areaByRadius(4.0) - areaByRadius(3.0);

  EXPECT_NEAR(costs.concrete_cost, expected_area * 1000.0, kTolerance);
}

TEST(PoolTask, FenceCostUsesOuterCircumference) {
  const PoolCosts costs = solvePoolTask();

  EXPECT_NEAR(costs.fence_cost, circumferenceByRadius(4.0) * 2000.0,
              kTolerance);
}

TEST(PoolTask, BothMaterialEstimatesArePositive) {
  const PoolCosts costs = solvePoolTask();

  EXPECT_GT(costs.concrete_cost, 0.0);
  EXPECT_GT(costs.fence_cost, 0.0);
}

TEST(PoolTask, ConcreteCostMatchesNumericAnswer) {
  EXPECT_NEAR(solvePoolTask().concrete_cost, 21991.14857512855, 1e-6);
}

TEST(PoolTask, FenceCostMatchesNumericAnswer) {
  EXPECT_NEAR(solvePoolTask().fence_cost, 50265.48245743669, 1e-6);
}

TEST(PoolTask, TotalCostMatchesNumericAnswer) {
  const PoolCosts costs = solvePoolTask();

  EXPECT_NEAR(costs.concrete_cost + costs.fence_cost,
              72256.63103256524, 1e-6);
}
