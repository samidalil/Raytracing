#ifndef RT_LIGHT_H
#define RT_LIGHT_H

#include "Entity.h";
#include "Ray.h";
#include "../math/Vector.h";
#include "../math/Point.h";
#include "../texture/Color.h"
#include "../texture/Material.h"

class Light : public Entity {
private:
	void copy(const Light& l);
protected:
	virtual void display(std::ostream& os) const override;
public:
	Color id;
	Color is;
	float intensity;

	Light();
	Light(const Color& diffuse, const Color& specular, float intensity);
	Light(const Vector& position, const Vector& rotation, const Color& diffuse, const Color& specular, float intensity);
	Light(const Matrix& m, const Color& d, const Color& s, float i);
	Light(const Light& l);
	Light& operator=(const Light& l);
	
	Ray getRayToLight(const Point& p) const;
	Ray getRayFromLight(const Point& p) const;
	Vector getVectorToLight(const Point& p) const;
	Vector getVectorFromLight(const Point& p) const;

	virtual Color getIlluminationLambert(const Point& impact, const Vector& normal, const Ray& ray, const Material& mat) const = 0;
	virtual Color getIlluminationPhong(const Point& impact, const Vector& normal, const Ray& ray, const Material& mat) const = 0;
};

#endif
