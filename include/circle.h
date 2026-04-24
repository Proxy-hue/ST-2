// Copyright 2022 UNN-CS
#ifndef INCLUDE_CIRCLE_H_
#define INCLUDE_CIRCLE_H_

class Circle {
 public:
  explicit Circle(double radius = 0.0);

  void setRadius(double radius);
  void setFerence(double ference);
  void setArea(double area);

  double getRadius() const;
  double getFerence() const;
  double getArea() const;

 private:
  double radius_;
  double ference_;
  double area_;

  static constexpr double PI = 3.14159265358979323846;
  void updateByRadius();
  void updateByFerence();
  void updateByArea();
};


#endif  // INCLUDE_CIRCLE_H_
