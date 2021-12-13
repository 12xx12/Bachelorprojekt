//
// Created by marc_ on 24.11.2021.
//

#pragma once

#include <iostream>

class Matrix {
 public:
  Matrix();
  Matrix(double x_1, double y_1, double x_2, double y_2);

  Matrix operator+=(const Matrix& other);

  double x_1;
  double y_1;
  double x_2;
  double y_2;
};

extern std::ostream & operator<<(std::ostream& os, const Matrix& matrix);
extern inline Matrix operator*(double scalar, const Matrix& matrix);
extern inline bool operator==(const Matrix& lhs, const Matrix& rhs);
