// Copyright 2022 UNN-CS
#include "circle.h"

#include <cmath>
#include <stdexcept>

namespace {

void ensureNonNegative(double value, const char* value_name) {
  if (value < 0.0) {
    throw std::invalid_argument(value_name);
  }
}

}  // namespace

void Circle::rebuildFromRadius(double radius) {
  ensureNonNegative(radius, "Circle radius must be non-negative");

  radius_ = radius;
  ference_ = 2.0 * kPi * radius_;
  area_ = kPi * radius_ * radius_;
}

void Circle::rebuildFromFerence(double ference) {
  ensureNonNegative(ference, "Circle circumference must be non-negative");

  ference_ = ference;
  radius_ = ference_ / (2.0 * kPi);
  area_ = ference_ * ference_ / (4.0 * kPi);
}

void Circle::rebuildFromArea(double area) {
  ensureNonNegative(area, "Circle area must be non-negative");

  area_ = area;
  radius_ = std::sqrt(area_ / kPi);
  ference_ = 2.0 * kPi * radius_;
}

Circle::Circle(double radius) : radius_(0.0), ference_(0.0), area_(0.0) {
  rebuildFromRadius(radius);
}

void Circle::setRadius(double radius) { rebuildFromRadius(radius); }

void Circle::setFerence(double ference) { rebuildFromFerence(ference); }

void Circle::setArea(double area) { rebuildFromArea(area); }

double Circle::getRadius() const {
  return radius_;
}

double Circle::getFerence() const {
  return ference_;
}

double Circle::getArea() const {
  return area_;
}
