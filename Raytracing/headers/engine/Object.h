#ifndef RT_OBJECT_H
#define RT_OBJECT_H

#include "Entity.h"
#include "Ray.h"
#include "../math/Point.h"
#include "../math/Vector.h"
#include "../texture/Material.h"

class Object : public Entity {
private:
	void copy(const Object& o);
public:
	Object() = default;
	Object(const Vector& position, const Vector& rotation, float scale);
	Object(const Object& o);
	Object& operator=(const Object& o);

	virtual bool intersect(const Ray& ray, Point& impact) const = 0;
	virtual Material getMaterial(const Point& impact) const;
	virtual Ray getNormal(const Point& impact, const Point& observator) const = 0;
};

#endif
