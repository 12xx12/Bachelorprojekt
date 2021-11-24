//
// Created by marc_ on 24.11.2021.
//

#include "Matrix.h"

Matrix::Matrix() {
  x_1 = 0;
  y_1 = 0;
  x_2 = 0;
  y_2 = 0;
}

Matrix::Matrix(double x_1, double y_1, double x_2, double y_2) {
  this->x_1 = x_1;
  this->y_1 = y_1;
  this->x_2 = x_2;
  this->y_2 = y_2;
}

Matrix Matrix::operator+=(const Matrix &other) {
  x_1 = x_1 + other.x_1;
  y_1 = y_1 + other.y_1;
  x_2 = x_2 + other.x_2;
  y_2 = y_2 + other.y_2;
  return *this;
}

std::ostream &operator<<(std::ostream &os, const Matrix &matrix) {
  os << "{(" << matrix.x_1 << ", " << matrix.y_1 << "), " << "(" << matrix.x_2 << ", " << matrix.y_2 << ")}";
  return os;
}

inline Matrix operator*(double scalar, const Matrix &other) {
  return Matrix(scalar * other.x_1, scalar * other.y_1, scalar * other.x_2, scalar * other.y_2);
}

inline bool operator==(const Matrix &lhs, const Matrix &rhs) {
  return lhs.x_1 == rhs.x_1 && lhs.y_1 == rhs.y_1 && lhs.x_2 == rhs.x_2 && lhs.y_2 == rhs.y_2;
}
