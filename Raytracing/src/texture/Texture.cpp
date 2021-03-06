#include "../../headers/texture/Texture.h"
#include "../../headers/helpers/Utility.h"

IdGenerator Texture::idGenerator;

Texture::Texture(const std::string& texturePath) :
	id(idGenerator.getId()),
	path(texturePath)
{
	this->image = std::make_shared<Image>(path);
}


Texture::Texture(const std::string& path, int id):path(path), id(id)
{
	this->image = std::make_shared<Image>(path);
}


void Texture::copy(const Texture& t)
{
	this->id = Texture::idGenerator.getId();
	this->path = t.path;
	this->image = t.image;
}

Texture& Texture::operator=(const Texture& t)
{
	this->copy(t);
	return (*this);
}

std::ostream& operator<<(std::ostream& os, const Texture& t)
{
	os << "\"path\": " << "\"" << Utility::escape(t.path) << "\", ";
	os << "\"id\": " << t.id;
	return os;
}