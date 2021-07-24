#define PI 3.141592
#include "../../headers/lights/PointLight.h"

PointLight::PointLight() : Light() {}

PointLight::PointLight(const Color& diffuse, const Color& specular, float intensity) : Light(diffuse, specular, intensity) {}

PointLight::PointLight(const Vector& position, const Vector& rotation, const Color& diffuse, const Color& specular, float intensity) :
	Light(position, rotation, diffuse, specular, intensity)
{}

Color PointLight::getIlluminationLambert(const Point& impact, const Vector& normal, const Ray& ray, const Material& mat) const {

	Vector dir = this->localToGlobal(Point()) - impact;
	float distToHit = dir.norm();
	dir.normalized(); // /!\ normalize before calculate dot product
	dir /= sqrtf(distToHit);
	float angle = Vector::dot(normal, dir);
	Color c = (angle < 0 ? Color::black : mat.kd * this->id * angle);

	float i = this->intensity / (4 * PI * distToHit); 	// that is it called a squared fall of 
	return c * i;
}

Color PointLight::getIlluminationPhong(const Point& impact, const Vector& normal, const Ray& ray, const Material& mat) const {
	const float rToNAngle = Vector::dot(
		ray.vector,
		Vector::reflect(this->getVectorToLight(impact), normal)
	);
	Color result = this->getIlluminationLambert(impact, normal, ray, mat);

	if (rToNAngle >= 0) result += mat.ks * this->is * pow(rToNAngle, mat.shininess);
	return result * this->intensity;
}
