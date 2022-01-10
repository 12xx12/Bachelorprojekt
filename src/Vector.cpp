//
// Copyright (C) 2021 Marc Lorenz
//

#include <sstream>
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

std::string Vector::toString() const {
  std::stringstream ss;
  ss << "(" << _x << ", " << _y << ")";
  return ss.str();
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

Vector Vector::operator+(const Vector &other) const {
  return {_x + other._x, _y + other._y};
}

Vector Vector::operator-(const Vector &other) const {
  return {_x - other._x, _y - other._y};
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

Vector Vector::operator*=(double factor) {
  _x *= factor;
  _y *= factor;
  return *this;
}

Vector Vector::operator-() const {
  return {-_x, -_y};
}

inline Vector operator*(double scalar, const Vector &other) {
  return {scalar * other.getX(), scalar * other.getY()};
}

inline Vector operator*(const Vector &other, double scalar) {
  return {scalar * other.getX(), scalar * other.getY()};
}

inline double operator*(const Vector &a, const Vector &b) {
  return a.getX() * b.getX() + a.getY() * b.getY();
}

// Vector multiplication
inline Matrix operator%(const Vector &a, const Vector &b) {
  return {a.getX() * b.getX(), a.getY() * b.getX(), a.getX() * b.getY(), a.getY() * b.getY()};
}

inline Vector operator/(const Vector &other, double scalar) {
  return {other.getX() / scalar, other.getY() / scalar};
}

inline Vector operator/(double scalar, const Vector &other) {
  return {other.getX() / scalar, other.getY() / scalar};
}
