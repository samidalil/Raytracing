#include "../../headers/texture/Material.h"

IdGenerator Material::idGenerator;

Material::Material() : id(idGenerator.getId()), shininess(0.5f) {}

Material::Material(Color ambient, Color diffuse, Color specular, float shiny) :
	id(idGenerator.getId()),
	ka(ambient),
	kd(diffuse),
	ks(specular),
	shininess(shiny) {}

Material::Material(const Material& m) {
	this->copy(m);
}

Material& Material::operator=(const Material& m) {
	this->copy(m);
	return (*this);
}

void Material::copy(const Material& m) {
	this->id = idGenerator.getId();
	this->ka = m.ka;
	this->kd = m.kd;
	this->ks = m.ks;
	this->shininess = m.shininess;
	this->texture = m.texture;
}

Material Material::getColor(float x, float y) const {
	if (!this->texture->texture) return (*this);
	const Color pixel = this->texture->texture->getColor(x, y);

	return Material(
		this->ka * pixel,
		this->kd * pixel,
		this->ks * pixel,
		shininess
	);
}

std::ostream& operator<<(std::ostream& os, const Material& m)
{
	os << "\"ka\": " << m.ka << ",";
	os << "\"kd\": " << m.kd << ",";
	os << "\"ks\": " << m.ks << ",";
	os << "\"shininess\": " << m.shininess;
	if (m.texture)
	{
		os << ",";
		os << "\"texture\": " << m.texture->id;
	}
	return os;
}
