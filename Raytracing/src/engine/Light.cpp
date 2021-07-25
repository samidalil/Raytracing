#include "../../headers/engine/Light.h"

Light::Light() : Entity(), id(Color::white), is(Color::white), intensity(1) {}

Light::Light(const Color& diffuse, const Color& specular, float i) : Entity(), id(diffuse), is(specular), intensity(i) {}

Light::Light(const Vector& position, const Vector& rotation, const Color& diffuse, const Color& specular, float _intensity) :
	Entity(position, rotation, 1),
	id(diffuse),
	is(specular),
	intensity(_intensity)
{}

Light::Light(const Matrix & m, const Color & d, const Color & s, float i) : Entity(m), id(d), is(s), intensity(i)
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

void Light::display(std::ostream& os) const
{
	Entity::display(os);
	os << ",";
	os << "\"id\": " << id << ",";
	os << "\"is\": " << is;
}

Ray Light::getRayToLight(const Point& p) const {
	return Ray(p, this->getVectorToLight(p));
}

Ray Light::getRayFromLight(const Point& p) const {
	return Ray(this->localToGlobal(Point()), this->getVectorFromLight(p));
}

Vector Light::getVectorToLight(const Point& p) const {
	return Vector(this->localToGlobal(Point()) - p).normalized();
}

Vector Light::getVectorFromLight(const Point& p) const {
	return Vector(p - this->localToGlobal(Point())).normalized();
}
