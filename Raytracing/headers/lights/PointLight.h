#ifndef RT_POINTLIGHT_H
#define RT_POINTLIGHT_H

#include "../engine/Light.h"

class PointLight : public Light {
public:
	PointLight();
	PointLight(const Color& diffuse, const Color& specular);
	PointLight(const Vector& position, const Vector& rotation, const Color& diffuse, const Color& specular);

	Color getIlluminationLambert(const Point& impact, const Vector& normal, const Ray& ray, const Material& mat) const override;
	Color getIlluminationPhong(const Point& impact, const Vector& normal, const Ray& ray, const Material& mat) const override;
};

#endif
