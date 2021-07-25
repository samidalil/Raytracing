#include "../../headers/primitives/Cube.h"
#include <algorithm>

std::string Cube::type() const
{
	return "\"Cube\"";
}

Cube::Cube(const Vector& position, const Vector& rotation, float scale, const std::shared_ptr<Material>& material) :
	Object(position, rotation, scale, material)
{}

Cube::Cube(const Matrix & m) : Object(m)
{}

bool Cube::intersect(const Ray& ray, Point& impact) const
{
	const Ray localRay = this->globalToLocal(ray);
	Vector invDir;

	invDir[0] = 1 / localRay.vector[0];
	invDir[1] = 1 / localRay.vector[1];
	invDir[2] = 1 / localRay.vector[2];

	float t1 = (-1 - localRay.origin[0]) * invDir[0];
	float t2 = (1 - localRay.origin[0]) * invDir[0];
	float t3 = (-1 - localRay.origin[1]) * invDir[1];
	float t4 = (1 - localRay.origin[1]) * invDir[1];
	float t5 = (-1 - localRay.origin[2]) * invDir[2];
	float t6 = (1 - localRay.origin[2]) * invDir[2];

	float tmin = std::max(std::max(std::min(t1, t2), std::min(t3, t4)), std::min(t5, t6));
	float tmax = std::min(std::min(std::max(t1, t2), std::max(t3, t4)), std::max(t5, t6));

	if (tmax < 0 || tmax < tmin) return false;

	impact[0] = localRay.origin[0] + localRay.vector[0] * tmin;
	impact[1] = localRay.origin[1] + localRay.vector[1] * tmin;
	impact[2] = localRay.origin[2] + localRay.vector[2] * tmin;

	impact = this->localToGlobal(impact);

	return true;
}

Ray Cube::getNormal(const Point& p, const Point& o) const
{
	Vector normal(0, 0, 0);
	const Point impact = this->globalToLocal(p);
	const Point observator = this->globalToLocal(o);
	const float limit = 1.0e-5f;

	for (int i = 0; i < 3; i++)
		if (abs(abs(impact[i]) - 1) <= limit)
		{
			normal[i] = impact[i] < 0 ? -1 : 1;
			if (observator[i] < 1 && observator[i] > -1)
				normal[i] *= -1;
		}

	return Ray(p, this->localToGlobal(normal).normalized());
}

Point Cube::getTextureCoordinates(const Point& p) const
{
	const Point impact = this->globalToLocal(p);

	if (impact[0] > 0.999 || impact[0] < -0.999)
		return Point(impact[2] / 2 + 0.5, impact[1] / 2 + 0.5, 0);
	if (impact[1] > 0.999 || impact[1] < -0.999)
		return Point(impact[0] / 2 + 0.5, impact[2] / 2 + 0.5, 0);
	if (impact[2] > 0.999 || impact[2] < -0.999)
		return Point(impact[0] / 2 + 0.5, impact[1] / 2 + 0.5, 0);
	return Point(0, 0, 0);
}
