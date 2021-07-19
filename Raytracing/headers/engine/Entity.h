#ifndef RT_ENTITY_H
#define RT_ENTITY_H

#include "../math/Matrix.h"
#include "../math/Vector.h"
#include "Ray.h"
#include <iostream>

class Entity {
private:
	Matrix _trans;
	Matrix _transInv;
public:
	Entity() = default;
	Entity(Vector position, Vector rotation, float scale);

	void rotate(Vector angles);
	void rotateX(float deg);
	void rotateY(float deg);
	void rotateZ(float deg);
	void scale(float factor);
	void translate(float x, float y, float z);
	void translate(Vector translation);

	Point localToGlobal(const Point& p) const;
	Vector localToGlobal(const Vector& v) const;
	Ray localToGlobal(const Ray& r) const;
	Point globalToLocal(const Point& p) const;
	Vector globalToLocal(const Vector& v) const;
	Ray globalToLocal(const Ray& r) const;

	friend std::ostream& operator<<(std::ostream& os, const Entity& e);
};

#endif
