#include "../../headers/primitives/Sphere.h"
#include "../../headers/math/Constants.h"

std::string Sphere::type() const
{
	return "\"Sphere\"";
}

Sphere::Sphere(const Vector& position, const Vector& rotation, float scale, const std::shared_ptr<Material>& material) :
	Object(position, rotation, scale, material)
{}

Sphere::Sphere(const Matrix & m) : Object(m)
{}

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

	return Ray(impact, (distance < 1 ? -1 : 1) * Vector(i).normalized());
}

Point Sphere::getTextureCoordinates(const Point& p) const
{
	Point coord = globalToLocal(p);
	Point lp = globalToLocal(p);
	float rho = std::sqrt(Point::dot(lp, lp));
	float theta = std::atan2(lp[1], lp[0]);
	float sigma = std::acos(lp[2] / rho);
	float x = -theta / (2 * PI) + 0.5;
	float y = sigma / PI;
	return Point(x, y, 0);

}
