#include "..\..\headers\engine\Skybox.h"

std::string Skybox::type() const
{
	return "\"Skybox\"";
}

Skybox::Skybox(const Camera& cam, float scale, const std::shared_ptr<Material>& material) :
	Sphere(cam.localToGlobal(Point()), Vector(-90, 0, 0), scale, material)
{
}
