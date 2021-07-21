#pragma once


#include "../engine/Object.h"
#include "../engine/Ray.h"
#include "../math/Point.h"
#include "../math/Vector.h"

class Plane : public Object {
public:
	Plane() = default;
	Plane(Vector position, Vector rotation, float scale);

	bool intersect(const Ray& ray, Point& impact) const override;
	Ray getNormal(const Point& impact, const Point& observator) const override;
};