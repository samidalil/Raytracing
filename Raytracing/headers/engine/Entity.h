#ifndef RT_ENTITY_H
#define RT_ENTITY_H

#include <iostream>
#include "Ray.h"
#include "../math/Matrix.h"
#include "../math/Vector.h"

class Entity {
private:
	Matrix _trans;
	Matrix _transInv;

	void rotate(const Vector& angles);
	void rotateX(float deg);
	void rotateY(float deg);
	void rotateZ(float deg);
	void scale(float factor);
	void translate(float x, float y, float z);
	void translate(const Vector& translation);
protected:
	virtual void copy(const Entity& e);
	virtual void display(std::ostream& os) const;
	virtual std::string type()const = 0;

public:
	Entity() = default;
	Entity(const Vector& position, const Vector& rotation, float scale);
	Entity(const Matrix& m);
	Entity(const Entity& e);
	Entity& operator=(const Entity& e);

	void apply(const Vector& position, const Vector& rotation, float scale);

	Point localToGlobal(const Point& p) const;
	Vector localToGlobal(const Vector& v) const;
	Ray localToGlobal(const Ray& r) const;
	Point globalToLocal(const Point& p) const;
	Vector globalToLocal(const Vector& v) const;
	Ray globalToLocal(const Ray& r) const;

	friend std::ostream& operator<<(std::ostream& os, const Entity& e);
};

#endif
