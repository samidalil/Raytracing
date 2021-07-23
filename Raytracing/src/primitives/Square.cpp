#include "../../headers/primitives/Square.h"
#include <algorithm>

Square::Square(const Vector& position, const Vector& rotation, float scale, const std::shared_ptr<Material>& material) :
	Object(position, rotation, scale, material)
{}

bool Square::intersect(const Ray& ray, Point& impact) const
{
	Ray lr = globalToLocal(ray).normalized();
	if (lr.vector[2]<0.0001 && lr.vector[2]>-0.0001)return false;
	if (lr.vector[2] * lr.origin[2] > 0)return false;
	float t = -lr.origin[2] / lr.vector[2];
	Point p = lr.origin + t * lr.vector;
	if (p[0] < -1 || p[0]>1 || p[1] < -1 || p[1]>1)return false;
	impact = localToGlobal(p);
	return true;
}

Ray Square::getNormal(const Point& impact, const Point& observator) const
{
	//TODO maybe do backface? 
	return Ray(impact, this->localToGlobal(Vector(0, 0, this->globalToLocal(observator)[2] < 0 ? -1 : 1)));
}

Point Square::getTextureCoordinates(const Point& p) const
{
	Point lp = globalToLocal(p);
	return Point(lp[0] / 2 + 0.5, lp[1] / 2 + 0.5, 0.0);
}
