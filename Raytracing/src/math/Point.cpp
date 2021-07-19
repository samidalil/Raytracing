#include "../../headers/math/Point.h"

Point::Point() {
	this->_tab[0] = 0;
	this->_tab[1] = 0;
	this->_tab[2] = 0;
}

Point::Point(float x, float y, float z) {
	this->_tab[0] = x;
	this->_tab[1] = y;
	this->_tab[2] = z;
}
Point::Point(const Point& v) {
	copy(v);
}

Point& Point::operator=(const Point& v) {
	copy(v);
	return (*this);
}

void Point::copy(const Point& v) {
	this->_tab[0] = v[0];
	this->_tab[1] = v[1];
	this->_tab[2] = v[2];
}

float Point::dot(const Point& a, const Point& b) {
	return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

float& Point::operator[](int index) {
	return this->_tab[index];
}

float Point::operator[](int index) const {
	return this->_tab[index];
}

Point Point::operator-() const {
	return Point(-this->_tab[0], -this->_tab[1], -this->_tab[2]);
}

Point& Point::operator+=(const Point& p) {
	this->_tab[0] += p[0];
	this->_tab[1] += p[1];
	this->_tab[2] += p[2];
	return (*this);
}

Point& Point::operator-=(const Point& p) {
	this->_tab[0] -= p[0];
	this->_tab[1] -= p[1];
	this->_tab[2] -= p[2];
	return (*this);
}

Point& Point::operator*=(float s) {
	this->_tab[0] *= s;
	this->_tab[1] *= s;
	this->_tab[2] *= s;
	return (*this);
}

Point& Point::operator/=(float s) {
	this->_tab[0] /= s;
	this->_tab[1] /= s;
	this->_tab[2] /= s;
	return (*this);
}

Point operator+(const Point& lhs, const Point& rhs) {
	Point p = lhs;
	return p += rhs;
}

Point operator-(const Point& lhs, const Point& rhs) {
	Point p = lhs;
	return p -= rhs;
}
Point operator*(const Point& lhs, float rhs) {
	Point p = lhs;
	return p *= rhs;
}

Point operator*(float lhs, const Point& rhs) {
	Point p = rhs;
	return p *= lhs;
}

Point operator/(const Point& lhs, float rhs) {
	Point p = lhs;
	return p /= rhs;
}

Point operator/(float lhs, const Point& rhs) {
	Point p = rhs;
	return p /= lhs;
}

std::ostream& operator<<(std::ostream& os, const Point& v) {
	os << "x: " << v[0] << ", y: " << v[1] << ", z: " << v[2];
	return os;
}
