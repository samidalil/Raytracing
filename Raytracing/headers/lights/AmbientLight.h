#ifndef RT_AMBIENTLIGHT_H
#define RT_AMBIENTLIGHT_H

#include "../engine/Light.h"

class AmbientLight : public Light {
public:
	AmbientLight();
	AmbientLight(const Color& diffuse, const Color& specular);
	AmbientLight(const Vector& position, const Vector& rotation, const Color& diffuse, const Color& specular);

	Color getIlluminationLambert(const Point& impact, const Vector& normal, const Ray& ray, const Material& mat) const override;
	Color getIlluminationPhong(const Point& impact, const Vector& normal, const Ray& ray, const Material& mat) const override;
};

#endif
