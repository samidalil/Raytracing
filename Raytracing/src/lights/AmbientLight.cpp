#include "../../headers/lights/AmbientLight.h"

AmbientLight::AmbientLight() : Light() {}

AmbientLight::AmbientLight(const Color& diffuse, const Color& specular) : Light(diffuse, specular) {}

AmbientLight::AmbientLight(const Vector& position, const Vector& rotation, const Color& diffuse, const Color& specular) :
	Light(position, rotation, diffuse, specular)
{}

Color AmbientLight::getIlluminationLambert(const Point& impact, const Vector& normal, const Ray& ray, const Material& mat) const {
	float angle = Vector::dot(normal, this->getVectorToLight(impact));

	return angle < 0 ? Color::black : mat.kd * this->id * angle;
}

Color AmbientLight::getIlluminationPhong(const Point& impact, const Vector& normal, const Ray& ray, const Material& mat) const {
	const float rToNAngle = Vector::dot(
		ray.vector,
		Vector::reflect(this->getVectorToLight(impact), normal)
	);
	Color result = this->getIlluminationLambert(impact, normal, ray, mat);

	if (rToNAngle >= 0) result += mat.ks * this->is * pow(rToNAngle, mat.shininess);
	return result;
}
