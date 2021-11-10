//
// Created by marc_ on 10.11.2021.
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

std::ostream & operator<<(std::ostream &os, const Vector & vec) {
	os << "(" << vec._x << ", " << vec._y << ")";
	return os;
}
