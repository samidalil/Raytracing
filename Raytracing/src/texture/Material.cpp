#include "../../headers/texture/Material.h"

Material::Material() : shininess(0.5f)
{
}

Material::Material(Color ambient, Color diffuse, Color specular, float shiny, Image tex) :
	ka(ambient),
	kd(diffuse),
	ks(specular),
	shininess(shiny),
	texture(tex)
{}

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
}