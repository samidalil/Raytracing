#ifndef RT_PLANE_H
#define RT_PLANE_H

#include "../engine/Object.h"
#include "../engine/Ray.h"
#include "../math/Point.h"
#include "../math/Vector.h"
#include "../texture/Material.h"

class Plane : public Object {
protected:
	std::string type() const override;
public:
	Plane() = default;
	Plane(const Vector& position, const Vector& rotation, float scale, const std::shared_ptr<Material>& material);
	Plane(const Matrix& m);

	bool intersect(const Ray& ray, Point& impact) const override;
	Ray getNormal(const Point& impact, const Point& observator) const override;
	Point getTextureCoordinates(const Point& p) const override;
};

#endif
