#include "../../headers/math/Vector.h"

#include <cmath>

Vector::Vector() : Point() {}

Vector::Vector(float x, float y, float z) : Point(x, y, z) {}

Vector::Vector(const Vector& v) : Point(v) {}

Vector::Vector(const Point& p) : Point(p) {}

Vector& Vector::operator=(const Vector& v) {
	Point::copy(v);
	return (*this);
}

Vector& Vector::operator=(const Point& p) {
	Point::copy(p);
	return (*this);
}

float Vector::norm() const {
	return sqrt(this->_tab[0] * this->_tab[0] + this->_tab[1] * this->_tab[1] + this->_tab[2] * this->_tab[2]);
}

Vector Vector::normalized() const {
	const float norm = this->norm();

	if (norm == 0) return (*this);
	return (*this) / norm;
}

Vector Vector::reflect(const Vector& v, const Vector& n)
{
	return v - n * (2 * Vector::dot(v, n));
}
