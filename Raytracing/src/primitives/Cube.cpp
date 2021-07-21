#include "../../headers/primitives/Cube.h"

float Cube::interSide(const Ray& r, int dim, float offset) const
{
	float t = -1;
	if (r.vector[dim]<0.00001 && r.vector[dim]>-0.00001)return -1;
	t = (offset - r.origin[dim]) / r.vector[dim];
	if (t < 0)return -1;
	for (int d = 0; d < 3; d++) {
		if (d == dim)continue;
		float x = r.origin[d] + t * r.vector[d];
		if (x < -1 || x > 1)return -1;
	}
	return t;
}

Cube::Cube(Vector position, Vector rotation, float scale) : Object(position, rotation, scale)
{
}

bool Cube::intersect(const Ray& ray, Point& impact) const
{
	Ray r = globalToLocal(ray).normalized();

	float mint = -1;
	float offsets[] = { -1,1 };
	for (int d = 0; d < 3; d++) {
		for (int o = 0; o < 2; o++) {
			float t = interSide(r, d, offsets[o]);
			if (t >= 0 && (mint<0 || mint>t)) {
				mint = t;
			}
		}
	}

	if (mint >= 0) {
		impact = localToGlobal(r.origin + mint * r.vector);
		return true;
	}

	return false;
}

Ray Cube::getNormal(const Point& p, const Point& o) const
{
    Point i = globalToLocal(p);
    Point obs = globalToLocal(o);
    Vector n(0, 0, 0);
    float eps = 0.01;

    if (abs(i[0] - 1) < eps) n[0] = 1;
    if (abs(i[1] - 1) < eps) n[1] = 1;
    if (abs(i[2] - 1) < eps) n[2] = 1;

    if (abs(i[0] + 1) < eps) n[0] = -1;
    if (abs(i[1] + 1) < eps) n[1] = -1;
    if (abs(i[2] + 1) < eps) n[2] = -1;


    if (obs[0]<1 && obs[0]>-1 && obs[1]<1 && obs[1]>-1 && obs[2]<1 && obs[2]>-1)
    {
        n = -1 * n;
    }

    n = localToGlobal(n).normalized();
    return Ray(p, n);
}
