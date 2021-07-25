#include "../../headers/texture/Texture.h"


Texture::Texture(const std::string& texturePath):path(texturePath)
{
	id = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	//texture = std::make_shared<Image>(texture);
}

Texture::Texture(){
	id = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
}

void Texture::copy(const Texture& t)
{
	this->path = t.path;
	this->id = t.id;
	this->texture = t.texture;
}

Texture& Texture::operator=(const Texture& t)
{
	this->copy(t);
	return (*this);
}

std::ostream& operator<<(std::ostream& os, const Texture& t)
{
	os << "\"path\": " << "\"" << t.path << "\", "; 
	os << "\"id\": " << t.id.count();
	return os;
}