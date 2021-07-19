#ifndef RT_POINT_H
#define RT_POINT_H

#include <iostream>

class Point {
protected:
	// Tableau contenant les valeurs x, y et z
	float _tab[3];

	void copy(const Point& p);
public:
	Point();
	Point(float x, float y, float z);
	Point(const Point& p);
	Point& operator=(const Point& p);

	static float dot(const Point& a, const Point& b);

	float& operator[](int index);
	float operator[](int index) const;
	Point operator-() const;
	Point& operator+=(const Point& p);
	Point& operator-=(const Point& p);
	Point& operator*=(float s);
	Point& operator/=(float s);

	friend Point operator+(const Point& lhs, const Point& rhs);
	friend Point operator-(const Point& lhs, const Point& rhs);
	friend Point operator*(const Point& v, float s);
	friend Point operator*(float s, const Point& v);
	friend Point operator/(const Point& v, float s);
	friend Point operator/(float s, const Point& v);

	friend std::ostream& operator<<(std::ostream& os, const Point& v);
};

#endif
