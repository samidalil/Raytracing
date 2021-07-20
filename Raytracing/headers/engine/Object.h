#ifndef RT_OBJECT_H
#define RT_OBJECT_H

#include "Entity.h"
#include "Ray.h"
#include "../math/Point.h"
#include "../math/Vector.h"
#include "../texture/Material.h"

class Object : public Entity {
public:
	Object() = default;
	Object(Vector position, Vector rotation, float scale);

	virtual bool intersect(const Ray& ray, Point& impact) const = 0;
	virtual Material getMaterial(const Point& impact) const;
	virtual Ray getNormal(const Point& impact, const Point& observator) const = 0;
};

#endif
