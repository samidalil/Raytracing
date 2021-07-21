#include "../../headers/engine/Object.h"


Object::Object(const Vector& position, const Vector& rotation, float scale) : Entity(position, rotation, scale) {}




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

	return Material({ 0.8f,0.1f, 0.5f }, { 0.5f,0.2f,0.3f }, {1,1,1}, 5);
}
