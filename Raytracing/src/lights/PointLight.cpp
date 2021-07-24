#define PI 3.141592
#include "../../headers/lights/PointLight.h"

PointLight::PointLight() : Light() {}

PointLight::PointLight(const Color& diffuse, const Color& specular, float intensity) : Light(diffuse, specular, intensity) {}

PointLight::PointLight(const Vector& position, const Vector& rotation, const Color& diffuse, const Color& specular, float intensity) :
	Light(position, rotation, diffuse, specular, intensity)
{}

Color PointLight::getIlluminationLambert(const Point& impact, const Vector& normal, const Ray& ray, const Material& mat) const {
	
	
    Vector dir = this->getVectorToLight(impact);
	float distance = sqrtf(dir.norm());
	float angle = Vector::dot(normal, dir/distance);

	return  (angle < 0 ? Color::black : mat.kd * this->id * angle) * this->intensity;
}

Color PointLight::getIlluminationPhong(const Point& impact, const Vector& normal, const Ray& ray, const Material& mat) const {

}
