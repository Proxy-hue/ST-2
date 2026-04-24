// Copyright 2022 UNN-CS
#include "circle.h"

#include <cmath>
#include <stdexcept>

void Circle::updateByRadius() {
  ference_ = 2.0 * PI * radius_;
  area_ = PI * radius_ * radius_;
}

void Circle::updateByFerence() {
  radius_ = ference_ / (2.0 * PI);
  area_ = PI * radius_ * radius_;
}

void Circle::updateByArea() {
  radius_ = std::sqrt(area_ / PI);
  ference_ = 2.0 * PI * radius_;
}

Circle::Circle(double radius) : radius_(0.0), ference_(0.0), area_(0.0) {
  setRadius(radius);
}

void Circle::setRadius(double radius) {
  if (radius < 0.0) {
    throw std::invalid_argument("Radius cannot be negative");
  }
  radius_ = radius;
  updateByRadius();
}

void Circle::setFerence(double ference) {
  if (ference < 0.0) {
    throw std::invalid_argument("Ference cannot be negative");
  }
  ference_ = ference;
  updateByFerence();
}

void Circle::setArea(double area) {
  if (area < 0.0) {
    throw std::invalid_argument("Area cannot be negative");
  }
  area_ = area;
  updateByArea();
}

double Circle::getRadius() const {
  return radius_;
}

double Circle::getFerence() const {
  return ference_;
}

double Circle::getArea() const {
  return area_;
}
