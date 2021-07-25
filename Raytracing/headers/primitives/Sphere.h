#ifndef RT_SPHERE_H
#define RT_SPHERE_H

#include "../engine/Object.h"
#include "../engine/Ray.h"
#include "../math/Point.h"
#include "../math/Vector.h"
#include "../texture/Material.h"

class Sphere : public Object {
protected:
	std::string type() const override;
public:
	Sphere() = default;
	Sphere(const Vector& position, const Vector& rotation, float scale, const std::shared_ptr<Material>& material);

	bool intersect(const Ray& ray, Point& impact) const override;
	Ray getNormal(const Point& impact, const Point& observator) const override;
	Point getTextureCoordinates(const Point& p) const override;
};

#endif
