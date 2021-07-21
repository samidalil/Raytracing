#ifndef RT_SPHERE_H
#define RT_SPHERE_H

#include "../engine/Object.h"
#include "../engine/Ray.h"
#include "../math/Point.h"
#include "../math/Vector.h"

class Sphere : public Object {
public:
	Sphere() = default;
	Sphere(Vector position, Vector rotation, float scale);

	bool intersect(const Ray& ray, Point& impact) const override;
	Ray getNormal(const Point& impact, const Point& observator) const override;
	virtual Point getTextureCoordinates(const Point& p)  const override;
};

#endif
