#define EPS 0.0000001
#include "../../headers/primitives/Triangle.h"
#include "../../headers/math/Constants.h" 

Triangle::Triangle(const Vector& position, const Vector& rotation, float scale, const std::shared_ptr<Material>& material) : 
	Object(position, rotation, scale, material), _uv(Point())
{
}

Point Triangle::A(-1, -1, 0);
Point Triangle::B(0, 1, 0);
Point Triangle::C(1, -1, 0);

// MOLLER TRUMBORE 
bool Triangle::intersect(const Ray& r, Point& impact) const
{
	Ray ray = globalToLocal(r);
	
	Vector AB = B - A;
	Vector BC = C - B;
	Vector h = Vector::cross(ray.vector, (BC));
	float det = Vector::dot(AB, h);
	if (det > -EPS && det < EPS) return false;    // parallel

	float invDet = 1.0 / det;
	Vector OA = ray.origin - A;
	float u = invDet * (Vector::dot(OA, h));
	if (u < 0.0 || u > 1.0)	return false;

	Vector q = Vector::cross(OA, AB);
	float v = invDet * Vector::dot(ray.vector, q);
	if (v < 0.0 || u + v > 1.0)	return false;

	float t = invDet * Vector::dot(BC, q); // impact at t * ray.vector

	if (t > EPS) // front face
	{
		impact = localToGlobal(ray.origin + ray.vector * t);
		return true;
	}
	else return false; // back face
}

Ray Triangle::getNormal(const Point& impact, const Point& observator) const
{

	return Ray(localToGlobal(Point(0,0,0)), localToGlobal(Vector::cross(Vector(B-A), Vector(C-B)))).normalized();
}

Point Triangle::getTextureCoordinates(const Point& p) const
{
	return Point();
}
