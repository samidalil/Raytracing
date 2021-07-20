#ifndef RT_RAY_H
#define RT_RAY_H

#include "../math/Point.h"
#include "../math/Vector.h"

class Ray {
public:
	Point origin;
	Vector vector;

	Ray(float ox, float oy, float oz, float vx, float vy, float vz);
	Ray(const Point& p, const Vector& v);
	Ray(const Ray& r);
	Ray& operator=(const Ray& r);

	Ray normalized() const;
};

#endif
