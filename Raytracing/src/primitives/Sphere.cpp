#define PI 3.151492
#include "../../headers/primitives/Sphere.h"

Sphere::Sphere(Vector position, Vector rotation, float scale) : Object(position, rotation, scale) {}

bool Sphere::intersect(const Ray& ray, Point& impact) const {
	const Ray localRay = this->globalToLocal(ray);

	const float c = localRay.origin[0] * localRay.origin[0]
		+ localRay.origin[1] * localRay.origin[1]
		+ localRay.origin[2] * localRay.origin[2]
		- 1;

	if (c == 0)
	{
		impact = ray.origin;
		return true;
	}

	const float a = localRay.vector[0] * localRay.vector[0]
		+ localRay.vector[1] * localRay.vector[1]
		+ localRay.vector[2] * localRay.vector[2];
	const float b = 2 *
		(localRay.vector[0] * localRay.origin[0]
			+ localRay.vector[1] * localRay.origin[1]
			+ localRay.vector[2] * localRay.origin[2]);
	const float delta = b * b - 4 * a * c;

	if (delta < 0) return false;

	float t;

	if (delta > 0)
	{
		if ((t = (-b - sqrt(delta)) / (2 * a)) <= 0)
			if ((t = (-b + sqrt(delta)) / (2 * a)) <= 0) return false;
	}
	else t = -b / (2 * a);

	impact[0] = localRay.origin[0] + localRay.vector[0] * t;
	impact[1] = localRay.origin[1] + localRay.vector[1] * t;
	impact[2] = localRay.origin[2] + localRay.vector[2] * t;

	impact = this->localToGlobal(impact);

	return true;
}

Ray Sphere::getNormal(const Point& impact, const Point& observator) const
{
	const Point i = this->globalToLocal(impact);
	const Point p = this->globalToLocal(observator);
	const float distance = p[0] * p[0] + p[1] * p[1] + p[2] * p[2];

	return Ray(impact, (distance < 1 ? -1 : 1) * Vector(i[0], i[1], i[2]).normalized());
}

Point Sphere::getTextureCoordinates(const Point& p) const
{
	Point coord = globalToLocal(p);

	return Point((-std::atan2(coord[1], coord[0]) / (2 * PI)) + 0.5,
		0.5 - (std::asin(coord[2]) / PI), 0);
}
