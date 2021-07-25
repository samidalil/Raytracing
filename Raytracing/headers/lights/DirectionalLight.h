#ifndef RT_DIRECTIONALLIGHT_H
#define RT_DIRECTIONALLIGHT_H

#include "../engine/Light.h"

class DirectionalLight : public Light {
protected:
	std::string type() const override;
public:
	DirectionalLight();
	DirectionalLight(const Color& diffuse, const Color& specular);
	DirectionalLight(const Vector& position, const Vector& rotation, const Color& diffuse, const Color& specular);
	DirectionalLight(const Matrix& m, const Color& d, const Color& s);

	Color getIlluminationLambert(const Point& impact, const Vector& normal, const Ray& ray, const Material& mat) const override;
	Color getIlluminationPhong(const Point& impact, const Vector& normal, const Ray& ray, const Material& mat) const override;
};

#endif
