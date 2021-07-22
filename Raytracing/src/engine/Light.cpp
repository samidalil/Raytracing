#include "../../headers/engine/Light.h"

Light::Light() : Entity(), id(Color::white), is(Color::white) {}

Light::Light(const Color& diffuse, const Color& specular) : Entity(), id(diffuse), is(specular) {}

Light::Light(const Vector& position, const Vector& rotation, const Color& diffuse, const Color& specular) :
	Entity(position, rotation, 1),
	id(diffuse),
	is(specular)
{}

Light::Light(const Light& l) {
	this->copy(l);
}

Light& Light::operator=(const Light& l) {
	this->copy(l);
	return (*this);
}

void Light::copy(const Light& l) {
	Entity::copy(l);
	this->id = l.id;
	this->is = l.is;
}

Ray Light::getRayToLight(const Point& p) const {
	return Ray(p, this->getVectorToLight(p));
}

Ray Light::getRayFromLight(const Point& p) const {
	return Ray(p, this->getVectorFromLight(p));
}

Vector Light::getVectorToLight(const Point& p) const {
	return Vector(this->localToGlobal(Point()) - p).normalized();
}

Vector Light::getVectorFromLight(const Point& p) const {
	return Vector(p - this->localToGlobal(Point())).normalized();
}
