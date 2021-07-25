#include "../../headers/engine/Entity.h"

Entity::Entity(const Vector& position, const Vector& rotation, float scale) {
	this->scale(scale);
	this->rotate(rotation);
	this->translate(position);
}

Entity::Entity(const Entity& e) {
	this->copy(e);
}

Entity& Entity::operator=(const Entity& e) {
	this->copy(e);
	return (*this);
}

void Entity::copy(const Entity& e) {
	this->_trans = e._trans;
	this->_transInv = e._transInv;
}

void Entity::display(std::ostream& os) const
{
	os << "\"type\": " << this->type();
	os << this->_trans;
}


void Entity::rotate(const Vector& angles) {
	this->rotateY(angles[1]);
	this->rotateZ(angles[2]);
	this->rotateX(angles[0]);
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
	const float c = cos(deg);
	const float s = sin(deg);
	m(0, 0) = c;
	m(0, 2) = s;
	m(2, 0) = -s;
	m(2, 2) = c;

	this->_trans = m * this->_trans;
	this->_transInv = this->_trans.inverse();
}

void Entity::rotateZ(float deg) {
	Matrix m;
	const float c = cos(deg);
	const float s = sin(deg);
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

void Entity::translate(const Vector& translation) {
	this->translate(translation[0], translation[1], translation[2]);
}

void Entity::apply(const Vector& position, const Vector& rotation, float scale) {
	this->_trans = Matrix();

	this->scale(scale);
	this->rotate(rotation);
	this->translate(position);
}

Point Entity::localToGlobal(const Point& p) const {
	return this->_trans * p;
}
Vector Entity::localToGlobal(const Vector& v) const {
	return this->_trans * v;
}

Ray Entity::localToGlobal(const Ray& r) const {
	return Ray(this->localToGlobal(r.origin), this->localToGlobal(r.vector));
}

Point Entity::globalToLocal(const Point& p) const {
	return this->_transInv * p;
}

Vector Entity::globalToLocal(const Vector& v) const {
	return this->_transInv * v;
}

Ray Entity::globalToLocal(const Ray& r) const {
	return Ray(this->globalToLocal(r.origin), this->globalToLocal(r.vector));
}

std::ostream& operator<<(std::ostream& os, const Entity& e) {
	//Debug operator << 
	/*os << "Transform:" << std::endl << e._trans << std::endl << "Inverse transform:" << std::endl << e._transInv;
	return os;*/
	e.display(os);
	return os;

}
