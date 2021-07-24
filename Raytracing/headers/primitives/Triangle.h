#pragma once

#include "../engine/Object.h"
#include "../engine/Ray.h"
#include "../math/Point.h"
#include "../math/Vector.h"
#include "../texture/Material.h"

class Triangle : public Object {

public:
	Triangle() = default;
	Triangle(const Vector& position, const Vector& rotation, float scale, const std::shared_ptr<Material>& material);
	static Point A;
	static Point B;
	static Point C;
	bool intersect(const Ray& ray, Point& impact) const override;
	Ray getNormal(const Point& impact, const Point& observator) const override;
	Point getTextureCoordinates(const Point& p) const override;
};
