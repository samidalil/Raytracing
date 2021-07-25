#ifndef RT_CYLINDER_H
#define RT_CYLINDER_H

#include "../engine/Object.h"
#include "../engine/Ray.h"
#include "../math/Point.h"
#include "../math/Vector.h"
#include "../texture/Material.h"

class Cylinder : public Object {
protected:
	std::string type() const override;
public:
	Cylinder() = default;
	Cylinder(const Vector& position, const Vector& rotation, float scale, const std::shared_ptr<Material>& material);

	bool intersect(const Ray& ray, Point& impact) const override;
	Ray getNormal(const Point& impact, const Point& observator) const override;
	Point getTextureCoordinates(const Point& p) const override;
};

#endif