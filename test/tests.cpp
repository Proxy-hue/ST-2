// Copyright 2022 UNN-CS Team

#include <cmath>

#include <gtest/gtest.h>

#include "circle.h"
#include "tasks.h"

const double EPS = 1e-5;
const double PI = 3.14159265358979323846;

TEST(st2, circle1) {
  Circle circle;
  EXPECT_NEAR(circle.getRadius(), 0.0, EPS);
  EXPECT_NEAR(circle.getFerence(), 0.0, EPS);
  EXPECT_NEAR(circle.getArea(), 0.0, EPS);
}

TEST(st2, circle2) {
  const double radius = 7.5;
  Circle circle(radius);
  EXPECT_NEAR(circle.getRadius(), radius, EPS);
  EXPECT_NEAR(circle.getFerence(), 2.0 * PI * radius, EPS);
  EXPECT_NEAR(circle.getArea(), PI * radius * radius, EPS);
}

TEST(st2, circle3) {
  Circle circle(0.0);
  EXPECT_NEAR(circle.getRadius(), 0.0, EPS);
  EXPECT_NEAR(circle.getFerence(), 0.0, EPS);
  EXPECT_NEAR(circle.getArea(), 0.0, EPS);
}

TEST(st2, circle4) {
  EXPECT_ANY_THROW(Circle(-10.5));
}

TEST(st2, circle5) {
  Circle circle(2.0);
  const double new_radius = 4.5;
  circle.setRadius(new_radius);
  EXPECT_NEAR(circle.getRadius(), new_radius, EPS);
  EXPECT_NEAR(circle.getFerence(), 2.0 * PI * new_radius, EPS);
  EXPECT_NEAR(circle.getArea(), PI * new_radius * new_radius, EPS);
}

TEST(st2, circle6) {
  Circle circle(3.0);
  const double original_radius = circle.getRadius();
  EXPECT_ANY_THROW(circle.setRadius(-2.5));
  EXPECT_NEAR(circle.getRadius(), original_radius, EPS);
}

TEST(st2, circle7) {
  Circle circle(1.0);
  const double new_ference = 31.4159;
  circle.setFerence(new_ference);
  const double expected_radius = new_ference / (2.0 * PI);
  EXPECT_NEAR(circle.getRadius(), expected_radius, EPS);
  EXPECT_NEAR(circle.getFerence(), new_ference, EPS);
  EXPECT_NEAR(circle.getArea(), PI * expected_radius * expected_radius, EPS);
}

TEST(st2, circle8) {
  Circle circle(3.0);
  const double original_ference = circle.getFerence();
  EXPECT_ANY_THROW(circle.setFerence(-15.0));
  EXPECT_NEAR(circle.getFerence(), original_ference, EPS);
}

TEST(st2, circle9) {
  Circle circle(1.0);
  const double new_area = 153.938;
  circle.setArea(new_area);
  const double expected_radius = std::sqrt(new_area / PI);
  EXPECT_NEAR(circle.getRadius(), expected_radius, EPS);
  EXPECT_NEAR(circle.getFerence(), 2.0 * PI * expected_radius, EPS);
  EXPECT_NEAR(circle.getArea(), new_area, EPS);
}

TEST(st2, circle10) {
  Circle circle(3.0);
  const double original_area = circle.getArea();
  EXPECT_ANY_THROW(circle.setArea(-20.0));
  EXPECT_NEAR(circle.getArea(), original_area, EPS);
}

TEST(st2, circle11) {
  Circle circle(8.8);
  circle.setRadius(0.0);
  EXPECT_NEAR(circle.getRadius(), 0.0, EPS);
  EXPECT_NEAR(circle.getFerence(), 0.0, EPS);
  EXPECT_NEAR(circle.getArea(), 0.0, EPS);
}

TEST(st2, circle12) {
  Circle circle(8.8);
  circle.setFerence(0.0);
  EXPECT_NEAR(circle.getRadius(), 0.0, EPS);
  EXPECT_NEAR(circle.getFerence(), 0.0, EPS);
  EXPECT_NEAR(circle.getArea(), 0.0, EPS);
}

TEST(st2, circle13) {
  Circle circle(8.8);
  circle.setArea(0.0);
  EXPECT_NEAR(circle.getRadius(), 0.0, EPS);
  EXPECT_NEAR(circle.getFerence(), 0.0, EPS);
  EXPECT_NEAR(circle.getArea(), 0.0, EPS);
}

TEST(st2, circle14) {
  Circle circle(9.0);
  circle.setRadius(1.5);
  circle.setFerence(18.8495);
  circle.setArea(50.2654);
  const double expected_radius = 4.0;
  EXPECT_NEAR(circle.getRadius(), expected_radius, 0.1);
  EXPECT_NEAR(circle.getFerence(), 2.0 * PI * expected_radius, 0.1);
  EXPECT_NEAR(circle.getArea(), PI * expected_radius * expected_radius, 0.1);
}

TEST(st2, circle15) {
  Circle circle(6.6);
  const double radius = circle.getRadius();
  EXPECT_NEAR(circle.getFerence() / (2.0 * radius), PI, EPS);
  EXPECT_NEAR(circle.getArea() / (radius * radius), PI, EPS);
}

TEST(st2, circle16) {
  const Circle circle(12.3);
  EXPECT_NEAR(circle.getRadius(), 12.3, EPS);
  EXPECT_NEAR(circle.getFerence(), 2.0 * PI * 12.3, EPS);
  EXPECT_NEAR(circle.getArea(), PI * 12.3 * 12.3, EPS);
}

TEST(st2, circle17) {
  Circle circle;
  const double test_area = 200.0;
  circle.setArea(test_area);
  const double calculated_ference = 2.0 * PI * std::sqrt(test_area / PI);
  EXPECT_NEAR(circle.getFerence(), calculated_ference, EPS);
}

TEST(st2, rope1) {
  EXPECT_GT(solveEarthRopeTask(), 0.0);
}

TEST(st2, rope2) {
  const double expected_gap = 1.0 / (2.0 * PI);
  EXPECT_NEAR(solveEarthRopeTask(), expected_gap, EPS);
}

TEST(st2, rope3) {
  EXPECT_NEAR(solveEarthRopeTask(), 0.159155, 1e-6);
}

TEST(st2, pool1) {
  const PoolCosts costs = solvePoolTask();
  Circle pool(3.0);
  Circle outer(pool.getRadius() + 1.0);
  const double expected_area = outer.getArea() - pool.getArea();
  EXPECT_NEAR(costs.concrete_cost / 1000.0, expected_area, EPS);
}

TEST(st2, pool2) {
  const PoolCosts costs = solvePoolTask();
  Circle outer(4.0);
  EXPECT_NEAR(costs.fence_cost / 2000.0, outer.getFerence(), EPS);
}

TEST(st2, pool3) {
  const PoolCosts costs = solvePoolTask();
  EXPECT_GT(costs.concrete_cost, 0.0);
}

TEST(st2, pool4) {
  const PoolCosts costs = solvePoolTask();
  EXPECT_GT(costs.fence_cost, 0.0);
}

TEST(st2, pool5) {
  const PoolCosts costs = solvePoolTask();
  EXPECT_NEAR(costs.concrete_cost, 21991.14857512855, 1e-3);
  EXPECT_NEAR(costs.fence_cost, 50265.48245743669, 1e-3);
}

TEST(st2, pool6) {
  const PoolCosts costs = solvePoolTask();
  EXPECT_NEAR(costs.concrete_cost + costs.fence_cost,
              72256.63103256524, 1e-3);
}
