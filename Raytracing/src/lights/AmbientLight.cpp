#include "../../headers/lights/AmbientLight.h"

std::string AmbientLight::type() const
{
	return "\"AmbientLight\"";
}

AmbientLight::AmbientLight() : Light() {}

AmbientLight::AmbientLight(const Color& diffuse, const Color& specular, float intensity) : Light(diffuse, specular, intensity) {}

AmbientLight::AmbientLight(const Vector& position, const Vector& rotation, const Color& diffuse, const Color& specular, float intensity) :
	Light(position, rotation, diffuse, specular, intensity)
{}

AmbientLight::AmbientLight(const Matrix& m, const Color& d, const Color& s, const float i) : Light(m, d, s, i)
{}

Color AmbientLight::getIlluminationLambert(const Point& impact, const Vector& normal, const Ray& ray, const Material& mat) const {
	float angle = Vector::dot(normal, this->getVectorToLight(impact));

	return (angle < 0 ? Color::black : mat.kd * this->id * angle);
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
