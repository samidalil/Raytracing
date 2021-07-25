#include "../../headers/engine/Object.h"


Object::Object(const Vector& position, const Vector& rotation, float scale, const std::shared_ptr<Material>& material) :
	Entity(position, rotation, scale),
	_material(material)
{}

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

void Object::display(std::ostream& os) const
{
	Entity::display(os);
	//todo add material id 
}


Material Object::getMaterial(const Point& impact) const {
	const Point coordinates = this->getTextureCoordinates(impact);
	return this->_material->getColor(coordinates[0], coordinates[1]);
}
