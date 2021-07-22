#include "../../headers/lights/PointLight.h"

PointLight::PointLight() : Light() {}

PointLight::PointLight(const Color& diffuse, const Color& specular) : Light(diffuse, specular) {}

PointLight::PointLight(const Vector& position, const Vector& rotation, const Color& diffuse, const Color& specular) :
	Light(position, rotation, diffuse, specular)
{}

Color PointLight::getIlluminationLambert(const Point& impact, const Vector& normal, const Ray& ray, const Material& mat) const {

}

Color PointLight::getIlluminationPhong(const Point& impact, const Vector& normal, const Ray& ray, const Material& mat) const {

}
