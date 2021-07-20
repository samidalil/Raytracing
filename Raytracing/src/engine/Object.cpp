#include "../../headers/engine/Object.h"


Object::Object(const Vector& position, const Vector& rotation, float scale, Material m) : Entity(position, rotation, scale), material(m) {}




Object::Object(const Object& o) {
	this->copy(o);
}

Object& Object::operator=(const Object& o) {
	this->copy(o);
	return (*this);
}

void Object::copy(const Object& o) {
	Entity::copy(o);
}


Material Object::getMaterial(const Point& impact) const{

	return this->material;
}
