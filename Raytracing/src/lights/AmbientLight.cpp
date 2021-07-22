#include "../../headers/lights/AmbientLight.h"

AmbientLight::AmbientLight() : Light() {}

AmbientLight::AmbientLight(const Color& diffuse, const Color& specular) : Light(diffuse, specular) {}

AmbientLight::AmbientLight(const Vector& position, const Vector& rotation, const Color& diffuse, const Color& specular) :
	Light(position, rotation, diffuse, specular)
{}

Color AmbientLight::getIlluminationLambert(const Point& impact, const Vector& normal, const Ray& ray, const Material& mat) const {
	float angle = Vector::dot(normal, this->getVectorToLight(impact));
	return mat.kd * this->id * (angle < 0 ? 0 : angle);
}

Color AmbientLight::getIlluminationPhong(const Point& impact, const Vector& normal, const Ray& ray, const Material& mat) const {
	const Vector r = this->getVectorToLight(impact);
	const float nToRAngle = Vector::dot(normal, r);
	const float rToNAngle = Vector::dot(ray.vector, Vector::reflect(r, normal));
	Color result;

	if (rToNAngle >= 0) result += mat.ks * this->is * pow(rToNAngle, mat.shininess);
	if (nToRAngle >= 0) result += mat.kd * this->id * nToRAngle;
	return result;
}
