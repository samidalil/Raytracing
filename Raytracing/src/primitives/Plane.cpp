#include "../../headers/primitives/Plane.h"

std::string Plane::type() const
{
    return "\"Plane\"";
}

Plane::Plane(const Vector& position, const Vector& rotation, float scale, const std::shared_ptr<Material>& material) :
	Object(position, rotation, scale, material)
{}

Plane::Plane(const Matrix & m) : Object(m)
{}

bool Plane::intersect(const Ray& ray, Point& impact) const
{
    const Ray localRay = this->globalToLocal(ray);

    if (localRay.origin[2] == 0)
    {
        impact[0] = ray.origin[0];
        impact[1] = ray.origin[1];
        impact[2] = ray.origin[2];

        return true;
    }
    if (localRay.vector[2] == 0
        || (localRay.vector[2] > 0 && localRay.origin[2] > 0)
        || (localRay.vector[2] < 0 && localRay.origin[2] < 0)
        )
        return false;

    float t = -localRay.origin[2] / localRay.vector[2];

    impact[0] = localRay.origin[0] + localRay.vector[0] * t;
    impact[1] = localRay.origin[1] + localRay.vector[1] * t;
    impact[2] = 0;

    impact = this->localToGlobal(impact);

    return true;
}

Ray Plane::getNormal(const Point& impact, const Point& observator) const {
	return Ray(impact, this->localToGlobal(Vector(0, 0, this->globalToLocal(observator)[2] < 0 ? -1 : 1)));
}

Point Plane::getTextureCoordinates(const Point& p) const
{
	Point coord = globalToLocal(p);
	float x = coord[0] - (int)coord[0];
	x += (x < 0);
	float y = coord[1] - (int)coord[1];
	y += (y < 0);

	return Point(x, y, 0);
}
