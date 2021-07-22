#include "../../headers/texture/Material.h"

Material::Material() : shininess(0.5f){}

Material::Material(Color ambient, Color diffuse, Color specular, float shiny) :
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
	this->ka = m.ka;
	this->kd = m.kd;
	this->ks = m.ks;
	this->shininess = m.shininess;
	this->texture = m.texture;
}

Material Material::getColor(float x, float y) const {
	if (!this->texture) return (*this);
	const Color pixel = this->texture->getColor(x, y);

	return Material(
		this->ka * pixel,
		this->kd * pixel,
		this->ks * pixel,
		shininess
	);
}
