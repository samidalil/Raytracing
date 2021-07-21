#pragma once


#include "../engine/Object.h"
#include "../engine/Ray.h"
#include "../math/Point.h"
#include "../math/Vector.h"

class Cube : public Object {
private :
	float interSide(const Ray& r, int dim, float offset) const;
public:
	Cube() = default;
	Cube(Vector position, Vector rotation, float scale);

	bool intersect(const Ray& ray, Point& impact) const override;
	Ray getNormal(const Point& impact, const Point& observator) const override;
};