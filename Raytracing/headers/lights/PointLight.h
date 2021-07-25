#ifndef RT_POINTLIGHT_H
#define RT_POINTLIGHT_H

#include "../engine/Light.h"

class PointLight : public Light {
protected:
	std::string type() const override;
public:
	PointLight();
	PointLight(const Color& diffuse, const Color& specular, float intensity);
	PointLight(const Vector& position, const Vector& rotation, const Color& diffuse, const Color& specular, float intensity);

	Color getIlluminationLambert(const Point& impact, const Vector& normal, const Ray& ray, const Material& mat) const override;
	Color getIlluminationPhong(const Point& impact, const Vector& normal, const Ray& ray, const Material& mat) const override;
};

#endif
