#include "../../headers/lights/DirectionalLight.h"

DirectionalLight::DirectionalLight() : Light() {}

DirectionalLight::DirectionalLight(const Color& diffuse, const Color& specular) : Light(diffuse, specular) {}

DirectionalLight::DirectionalLight(const Vector& position, const Vector& rotation, const Color& diffuse, const Color& specular) :
	Light(position, rotation, diffuse, specular)
{}

Color DirectionalLight::getIlluminationLambert(const Point& impact, const Vector& normal, const Ray& ray, const Material& mat) const {

}

Color DirectionalLight::getIlluminationPhong(const Point& impact, const Vector& normal, const Ray& ray, const Material& mat) const {

}