#include "../../headers/engine/Entity.h"

Entity::Entity(Vector position, Vector rotation, float scale) {
	this->translate(position);
	this->rotate(rotation);
	this->scale(scale);
}

void Entity::rotate(Vector angles) {
	this->rotateX(angles[0]);
	this->rotateY(angles[1]);
	this->rotateZ(angles[2]);
}

void Entity::rotateX(float deg) {
	Matrix m;
	float c = cos(deg);
	float s = sin(deg);
	m(1, 1) = c;
	m(1, 2) = -s;
	m(2, 1) = s;
	m(2, 2) = c;

	this->_trans = m * this->_trans;
	this->_transInv = this->_trans.inverse();
}

void Entity::rotateY(float deg) {
	Matrix m;
	float c = cos(deg);
	float s = sin(deg);
	m(0, 0) = c;
	m(0, 2) = s;
	m(2, 0) = -s;
	m(2, 2) = c;

	this->_trans = m * this->_trans;
	this->_transInv = this->_trans.inverse();
}

void Entity::rotateZ(float deg) {
	Matrix m;
	float c = cos(deg);
	float s = sin(deg);
	m(0, 0) = c;
	m(0, 1) = -s;
	m(1, 0) = s;
	m(1, 1) = c;

	this->_trans = m * this->_trans;
	this->_transInv = this->_trans.inverse();
}

void Entity::scale(float factor) {
	Matrix m;
	m(0, 0) = factor;
	m(1, 1) = factor;
	m(2, 2) = factor;

	this->_trans = m * this->_trans;
	this->_transInv = this->_trans.inverse();
}

void Entity::translate(float x, float y, float z) {
	Matrix m;
	m(0, 3) = x;
	m(1, 3) = y;
	m(2, 3) = z;

	this->_trans = m * this->_trans;
	this->_transInv = this->_trans.inverse();
}

void Entity::translate(Vector translation) {
	this->translate(translation[0], translation[1], translation[2]);
}

Point Entity::localToGlobal(const Point& p) const {
	return this->_transInv * p;
}
Vector Entity::localToGlobal(const Vector& v) const {
	return this->_transInv * v;
}

Ray Entity::localToGlobal(const Ray& r) const {
	return Ray(this->localToGlobal(r.origin), this->localToGlobal(r.vector));
}

Point Entity::globalToLocal(const Point& p) const {
	return this->_trans * p;
}

Vector Entity::globalToLocal(const Vector& v) const {
	return this->_trans * v;
}

Ray Entity::globalToLocal(const Ray& r) const {
	return Ray(this->globalToLocal(r.origin), this->globalToLocal(r.vector));
}

std::ostream& operator<<(std::ostream& os, const Entity& e) {
	os << "Transform:" << std::endl << e._trans << std::endl << "Inverse transform:" << std::endl << e._transInv;
	return os;
}