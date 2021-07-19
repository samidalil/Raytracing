#ifndef RT_VECTOR_H
#define RT_VECTOR_H

#include "Point.h"

class Vector : public Point {
public:
	Vector();
	Vector(float x, float y, float z);
	Vector(const Vector& v);
	Vector(const Point& p);
	Vector& operator=(const Vector& v);
	Vector& operator=(const Point& p);

	float norm() const;
	Vector normalized() const;
};

#endif
