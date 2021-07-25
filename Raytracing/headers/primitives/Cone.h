#ifndef RT_CONE_H
#define RT_CONE_H

#include "../engine/Object.h"
#include "../engine/Ray.h"
#include "../math/Point.h"
#include "../math/Vector.h"
#include "../texture/Material.h"

class Cone : public Object {
protected:
	std::string type() const override;
public:
	Cone() = default;
	Cone(const Vector& position, const Vector& rotation, float scale, const std::shared_ptr<Material>& material);
	Cone(const Matrix& m);

	bool intersect(const Ray& ray, Point& impact) const override;
	Ray getNormal(const Point& impact, const Point& observator) const override;
	Point getTextureCoordinates(const Point& p) const override;
};

#endif
