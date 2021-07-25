#ifndef RT_TRIANGLE_H
#define RT_TRIANGLE_H
#include "../engine/Object.h"
#include "../engine/Ray.h"
#include "../math/Point.h"
#include "../math/Vector.h"
#include "../texture/Material.h"

class Triangle : public Object {
protected:
	std::string type() const override;
public:
	static const Point A;
	static const Point B;
	static const Point C;
	static const Point AB;
	static const Point AC;
	static const Point BC;

	Triangle() = default;
	Triangle(const Vector& position, const Vector& rotation, float scale, const std::shared_ptr<Material>& material);
	Triangle(const Matrix& m);

	bool intersect(const Ray& ray, Point& impact) const override;
	Ray getNormal(const Point& impact, const Point& observator) const override;
	Point getTextureCoordinates(const Point& p) const override;
};
#endif
