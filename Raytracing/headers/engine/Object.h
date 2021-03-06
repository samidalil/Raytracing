#ifndef RT_OBJECT_H
#define RT_OBJECT_H

#include "Entity.h"
#include "Ray.h"
#include "../math/Point.h"
#include "../math/Vector.h"
#include "../texture/Material.h"

class Object : public Entity {
private:
	std::shared_ptr<Material> _material;

	void copy(const Object& o);
protected:
	virtual void display(std::ostream& os) const override;
public:
	Object(const Vector& position, const Vector& rotation, float scale, const std::shared_ptr<Material>& material);
	Object(const Matrix& m);
	Object(const Object& o);
	Object& operator=(const Object& o);

	virtual bool intersect(const Ray& ray, Point& impact) const = 0;
	virtual Material getMaterial(const Point& impact) const;
	void setMaterial(const std::shared_ptr<Material>& m);
	virtual Ray getNormal(const Point& impact, const Point& observator) const = 0;
	virtual Point getTextureCoordinates(const Point& p)  const = 0;
};

#endif
