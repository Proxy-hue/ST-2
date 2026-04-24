// Copyright 2022 UNN-CS Team

#include <cmath>
#include <stdexcept>

#include <gtest/gtest.h>

#include "circle.h"
#include "tasks.h"

const double EPS = 1e-5;
const double PI = 3.14159265358979323846;

TEST(CircleSpec, DefaultConstructorStartsAtZero) {
  Circle circle;
  EXPECT_NEAR(circle.getRadius(), 0.0, EPS);
  EXPECT_NEAR(circle.getFerence(), 0.0, EPS);
  EXPECT_NEAR(circle.getArea(), 0.0, EPS);
}

TEST(CircleSpec, ConstructorCalculatesDerivedValues) {
  const double radius = 7.5;
  Circle circle(radius);
  EXPECT_NEAR(circle.getRadius(), radius, EPS);
  EXPECT_NEAR(circle.getFerence(), 2.0 * PI * radius, EPS);
  EXPECT_NEAR(circle.getArea(), PI * radius * radius, EPS);
}

TEST(CircleSpec, ConstructorAllowsZeroRadius) {
  Circle circle(0.0);
  EXPECT_NEAR(circle.getRadius(), 0.0, EPS);
  EXPECT_NEAR(circle.getFerence(), 0.0, EPS);
  EXPECT_NEAR(circle.getArea(), 0.0, EPS);
}

TEST(CircleSpec, ConstructorRejectsNegativeRadius) {
  EXPECT_THROW(Circle(-10.5), std::invalid_argument);
}

TEST(CircleSpec, SetRadiusUpdatesAllValues) {
  Circle circle(2.0);
  const double new_radius = 4.5;
  circle.setRadius(new_radius);
  EXPECT_NEAR(circle.getRadius(), new_radius, EPS);
  EXPECT_NEAR(circle.getFerence(), 2.0 * PI * new_radius, EPS);
  EXPECT_NEAR(circle.getArea(), PI * new_radius * new_radius, EPS);
}

TEST(CircleSpec, SetRadiusRejectsNegativeValue) {
  Circle circle(3.0);
  const double original_radius = circle.getRadius();
  EXPECT_THROW(circle.setRadius(-2.5), std::invalid_argument);
  EXPECT_NEAR(circle.getRadius(), original_radius, EPS);
}

TEST(CircleSpec, SetFerenceUpdatesRadiusAndArea) {
  Circle circle(1.0);
  const double new_ference = 31.4159;
  circle.setFerence(new_ference);
  const double expected_radius = new_ference / (2.0 * PI);
  EXPECT_NEAR(circle.getRadius(), expected_radius, EPS);
  EXPECT_NEAR(circle.getFerence(), new_ference, EPS);
  EXPECT_NEAR(circle.getArea(), PI * expected_radius * expected_radius, EPS);
}

TEST(CircleSpec, SetFerenceRejectsNegativeValue) {
  Circle circle(3.0);
  const double original_ference = circle.getFerence();
  EXPECT_THROW(circle.setFerence(-15.0), std::invalid_argument);
  EXPECT_NEAR(circle.getFerence(), original_ference, EPS);
}

TEST(CircleSpec, SetAreaUpdatesRadiusAndFerence) {
  Circle circle(1.0);
  const double new_area = 153.938;
  circle.setArea(new_area);
  const double expected_radius = std::sqrt(new_area / PI);
  EXPECT_NEAR(circle.getRadius(), expected_radius, EPS);
  EXPECT_NEAR(circle.getFerence(), 2.0 * PI * expected_radius, EPS);
  EXPECT_NEAR(circle.getArea(), new_area, EPS);
}

TEST(CircleSpec, SetAreaRejectsNegativeValue) {
  Circle circle(3.0);
  const double original_area = circle.getArea();
  EXPECT_THROW(circle.setArea(-20.0), std::invalid_argument);
  EXPECT_NEAR(circle.getArea(), original_area, EPS);
}

TEST(CircleSpec, SettingRadiusToZeroClearsValues) {
  Circle circle(8.8);
  circle.setRadius(0.0);
  EXPECT_NEAR(circle.getRadius(), 0.0, EPS);
  EXPECT_NEAR(circle.getFerence(), 0.0, EPS);
  EXPECT_NEAR(circle.getArea(), 0.0, EPS);
}

TEST(CircleSpec, SettingFerenceToZeroClearsValues) {
  Circle circle(8.8);
  circle.setFerence(0.0);
  EXPECT_NEAR(circle.getRadius(), 0.0, EPS);
  EXPECT_NEAR(circle.getFerence(), 0.0, EPS);
  EXPECT_NEAR(circle.getArea(), 0.0, EPS);
}

TEST(CircleSpec, SettingAreaToZeroClearsValues) {
  Circle circle(8.8);
  circle.setArea(0.0);
  EXPECT_NEAR(circle.getRadius(), 0.0, EPS);
  EXPECT_NEAR(circle.getFerence(), 0.0, EPS);
  EXPECT_NEAR(circle.getArea(), 0.0, EPS);
}

TEST(CircleSpec, ChainedUpdatesRemainConsistent) {
  Circle circle(9.0);
  circle.setRadius(1.5);
  circle.setFerence(18.8495);
  circle.setArea(50.2654);
  const double expected_radius = 4.0;
  EXPECT_NEAR(circle.getRadius(), expected_radius, 0.1);
  EXPECT_NEAR(circle.getFerence(), 2.0 * PI * expected_radius, 0.1);
  EXPECT_NEAR(circle.getArea(), PI * expected_radius * expected_radius, 0.1);
}

TEST(CircleSpec, MathematicalRelationsHold) {
  Circle circle(6.6);
  const double radius = circle.getRadius();
  EXPECT_NEAR(circle.getFerence() / (2.0 * radius), PI, EPS);
  EXPECT_NEAR(circle.getArea() / (radius * radius), PI, EPS);
}

TEST(CircleSpec, ConstGetterAccessWorks) {
  const Circle circle(12.3);
  EXPECT_NEAR(circle.getRadius(), 12.3, EPS);
  EXPECT_NEAR(circle.getFerence(), 2.0 * PI * 12.3, EPS);
  EXPECT_NEAR(circle.getArea(), PI * 12.3 * 12.3, EPS);
}

TEST(CircleSpec, AreaRoundTripStaysStable) {
  Circle circle;
  const double test_area = 200.0;
  circle.setArea(test_area);
  const double calculated_ference = 2.0 * PI * std::sqrt(test_area / PI);
  EXPECT_NEAR(circle.getFerence(), calculated_ference, EPS);
}

TEST(EarthRopeSpec, GapIsPositive) {
  EXPECT_GT(solveEarthRopeTask(), 0.0);
}

TEST(EarthRopeSpec, GapMatchesClosedForm) {
  const double expected_gap = 1.0 / (2.0 * PI);
  EXPECT_NEAR(solveEarthRopeTask(), expected_gap, EPS);
}

TEST(EarthRopeSpec, GapHasExpectedMagnitude) {
  EXPECT_NEAR(solveEarthRopeTask(), 0.159155, 1e-6);
}

TEST(PoolSpec, ConcreteCostMatchesGeometry) {
  const PoolCosts costs = solvePoolTask();
  Circle pool(3.0);
  Circle outer(pool.getRadius() + 1.0);
  const double expected_area = outer.getArea() - pool.getArea();
  EXPECT_NEAR(costs.concrete_cost / 1000.0, expected_area, EPS);
}

TEST(PoolSpec, FenceCostMatchesOuterCircle) {
  const PoolCosts costs = solvePoolTask();
  Circle outer(4.0);
  EXPECT_NEAR(costs.fence_cost / 2000.0, outer.getFerence(), EPS);
}

TEST(PoolSpec, ConcreteCostIsPositive) {
  const PoolCosts costs = solvePoolTask();
  EXPECT_GT(costs.concrete_cost, 0.0);
}

TEST(PoolSpec, FenceCostIsPositive) {
  const PoolCosts costs = solvePoolTask();
  EXPECT_GT(costs.fence_cost, 0.0);
}

TEST(PoolSpec, CostsHaveExpectedApproximateValues) {
  const PoolCosts costs = solvePoolTask();
  EXPECT_NEAR(costs.concrete_cost, 21991.14857512855, 1e-3);
  EXPECT_NEAR(costs.fence_cost, 50265.48245743669, 1e-3);
}

TEST(PoolSpec, TotalCostMatchesSum) {
  const PoolCosts costs = solvePoolTask();
  EXPECT_NEAR(costs.concrete_cost + costs.fence_cost,
              72256.63103256524, 1e-3);
}
