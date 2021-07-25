#ifndef RT_AMBIENTLIGHT_H
#define RT_AMBIENTLIGHT_H

#include "../engine/Light.h"

class AmbientLight : public Light {
protected:
	std::string type() const override;
public:
	AmbientLight();
	AmbientLight(const Color& diffuse, const Color& specular, float intensity);
	AmbientLight(const Vector& position, const Vector& rotation, const Color& diffuse, const Color& specular, float intensity);

	Color getIlluminationLambert(const Point& impact, const Vector& normal, const Ray& ray, const Material& mat) const override;
	Color getIlluminationPhong(const Point& impact, const Vector& normal, const Ray& ray, const Material& mat) const override;
};

#endif
