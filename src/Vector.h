//
// Created by marc_ on 10.11.2021.
//

#pragma once

#include <ostream>

#include "Matrix.h"

class Vector {
 public:
  Vector();

  Vector(double x, double y);

  double getX() const;
  double getY() const;
  double distance(const Vector &other) const;

  std::string toString() const;

  bool operator==(const Vector &other) const;
  bool operator!=(const Vector &other) const;
  friend std::ostream &operator<<(std::ostream &os, const Vector &vec);

  Vector operator+(const Vector & other) const;
  Vector operator-(const Vector & other) const;

  Vector operator+= (const Vector & other);
  Vector operator-= (const Vector & other);
  Vector operator*= (double factor);
  Vector operator- () const;

 private:
  double _x;
  double _y;
};

extern inline Vector operator*(double scalar, const Vector & other);
extern inline Vector operator*(const Vector & other, double scalar);
extern inline double operator*(const Vector & a, const Vector & b);

extern inline Matrix operator%(const Vector & a, const Vector & b);

// division
extern inline Vector operator/(const Vector & other, double scalar);
extern inline Vector operator/(double scalar, const Vector & other);
