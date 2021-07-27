#include "..\..\headers\engine\Skybox.h"

std::string Skybox::type() const
{
	return "\"Skybox\"";
}

Skybox::Skybox(const Vector& position, float scale, const std::shared_ptr<Material>& material) :
	Sphere(position, Vector(-90, 0, 0), scale, material)
{
}
