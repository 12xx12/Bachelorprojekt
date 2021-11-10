//
// Copyright (C) 2021 Marc Lorenz
//

#include "Vector.h"

Vector::Vector() {
  _x = 0;
  _y = 0;
}

Vector::Vector(double x, double y) {
  _x = x;
  _y = y;
}

double Vector::getX() const {
  return _x;
}

double Vector::getY() const {
  return _y;
}

double Vector::distance(const Vector &other) const {
  return sqrt(pow(_x - other._x, 2) + pow(_y - other._y, 2));
}

bool Vector::operator==(const Vector &other) const {
  return _x == other._x && _y == other._y;
}

bool Vector::operator!=(const Vector &other) const {
  return !(*this == other);
}

std::ostream &operator<<(std::ostream &os, const Vector &vec) {
  os << "(" << vec._x << ", " << vec._y << ")";
  return os;
}

Vector Vector::operator+(const Vector & other) const {
  return Vector(_x + other._x, _y + other._y);
}

Vector Vector::operator-(const Vector & other) const {
  return Vector(_x - other._x, _y - other._y);
}

Vector Vector::operator+=(const Vector &other) {
  _x += other._x;
  _y += other._y;
  return *this;
}

Vector Vector::operator-=(const Vector &other) {
  _x -= other._x;
  _y -= other._y;
  return *this;
}

inline Vector operator*(double scalar, const Vector & other) {
  return Vector(scalar * other.getX(), scalar * other.getY());
}

inline Vector operator*(const Vector & other, double scalar) {
  return Vector(scalar * other.getX(), scalar * other.getY());
}

inline Vector operator/(const Vector & other, double scalar) {
  return Vector(other.getX() / scalar, other.getY() / scalar);
}

inline Vector operator/(double scalar, const Vector & other) {
  return Vector(other.getX() / scalar, other.getY() / scalar);
}
