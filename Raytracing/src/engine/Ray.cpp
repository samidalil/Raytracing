#include "../../headers/engine/Ray.h"

Ray::Ray(float ox, float oy, float oz, float vx, float vy, float vz) : origin(ox, oy, oz), vector(vx, vy, vz) {}

Ray::Ray(const Point& p, const Vector& v) : origin(p), vector(v) {}

Ray::Ray(const Ray& r) : origin(r.origin), vector(r.vector) {}

Ray& Ray::operator=(const Ray& r) {
	this->origin = r.origin;
	this->vector = r.vector;
	return (*this);
}
