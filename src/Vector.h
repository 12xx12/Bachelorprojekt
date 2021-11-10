//
// Created by marc_ on 10.11.2021.
//

#ifndef VECTOR_H_
#define VECTOR_H_


#include <ostream>

class Vector {
public:
	Vector();

	Vector(double x, double y);

	double getX() const;
	double getY() const;
	double distance(const Vector & other) const;

	bool operator==(const Vector& other) const;
	bool operator!=(const Vector& other) const;
	friend std::ostream & operator<<(std::ostream & os, const Vector & vec);

private:
	double _x;
	double _y;
};


#endif //VECTOR_H_
