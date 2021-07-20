#include "../../headers/engine/Light.h"

Light::Light(Color diffuse, Color specular) : Entity(), id(diffuse), is(specular) {}

Light::Light(Vector position, Vector rotation, Color diffuse, Color specular) :
	Entity(position, rotation, 1),
	id(diffuse),
	is(specular)
{}

Ray Light::getRayToLight(const Point& p) const {
	return Ray(p, this->getVectorToLight(p));
}

Ray Light::getRayFromLight(const Point& p) const {
	return Ray(p, this->getVectorFromLight(p));
}

Vector Light::getVectorToLight(const Point& p) const {
	Point position = this->localToGlobal(Point());

	return Vector(position - p).normalized();
}

Vector Light::getVectorFromLight(const Point& p) const {
	Point position = this->localToGlobal(Point());

	return Vector(p - position).normalized();
}
