#include "../../headers/primitives/Plane.h"

Plane::Plane(Vector position, Vector rotation, float scale) : Object(position, rotation, scale)
{
}

bool Plane::intersect(const Ray& ray, Point& impact) const
{
    Ray lr = globalToLocal(ray).normalized();
    if (lr.vector[2]<0.0001 && lr.vector[2]>-0.0001)return false;
    if (lr.vector[2] * lr.origin[2] > 0)return false;
    float t = -lr.origin[2] / lr.vector[2];
    Point p = lr.origin + t * lr.vector;
    impact = localToGlobal(p);
    return true;
}

Ray Plane::getNormal(const Point& impact, const Point& observator) const
{
    Point lp = globalToLocal(impact);
    Point lo = globalToLocal(observator);
    float z = 1;
    if (lo[2] < 0)z = -1;
    return localToGlobal(Ray(lp, Vector(0, 0, z))).normalized();
}
