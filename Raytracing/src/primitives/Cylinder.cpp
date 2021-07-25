#include "../../headers/primitives/Cylinder.h"
#include "../../headers/math/Constants.h"

std::string Cylinder::type() const
{
	return "\"Cylinder\"";
}

Cylinder::Cylinder(const Vector& position, const Vector& rotation, float scale, const std::shared_ptr<Material>& material) :
	Object(position, rotation, scale, material)
{}

bool Cylinder::intersect(const Ray& ray, Point& impact) const
{
	Ray r = globalToLocal(ray).normalized();

	float a = r.vector[0] * r.vector[0] + r.vector[2] * r.vector[2];
	float b = 2 * (r.vector[0] * r.origin[0] + r.vector[2] * r.origin[2]);
	float c = r.origin[0] * r.origin[0] + r.origin[2] * r.origin[2] - 1.0;
	float delta = b * b - 4 * a * c;

	if (delta < 0)return false;

	float t;
	if (delta < 0.0001) {
		t = -b / (2 * a);
	}
	else {
		t = (-b - sqrt(delta)) / (2 * a);
		if (t < 0)t = (-b + sqrt(delta)) / (2 * a);
	}
	if (t < 0)return false;

	Point p = r.origin + t * r.vector;
	impact = localToGlobal(p);
	return true;

}

Ray Cylinder::getNormal(const Point& impact, const Point& observator) const
{
	//TODO take solution of teacher from schooding but implem norm?
	Point imp = globalToLocal(impact);
	Point obs = globalToLocal(observator);

	float distance = sqrt(pow(obs[0], 2) + pow(obs[2], 2));

	Vector dir(imp[0], 0, imp[2]);

	if (distance < 1) dir = -1 * dir;

	Ray res(impact, localToGlobal(dir));
	return res;
}

Point Cylinder::getTextureCoordinates(const Point& p) const
{
	Point coord = globalToLocal(p);
	return Point(1 - (atan2(coord[0], coord[2]) / (2 * PI) + 0.5), std::fmod(coord[1], 1), 0);
}
