#ifndef RT_MATRIX_H
#define RT_MATRIX_H

#include "Point.h"
#include "Vector.h"
#include <iostream>

class Matrix {
private:
	// Tableau représentant une matrice 4*4 column-major order
	// Pour accéder à l'élément Mxy, on accède à la case x * 4 + y
	float _tab[16];

	void copy(const Matrix& m);
public:
	Matrix();
	Matrix(const Matrix& m);
	Matrix& operator=(const Matrix& m);

	Matrix inverse() const;

	float& operator()(int x, int y);
	float operator()(int x, int y) const;

	friend Matrix operator*(const Matrix& lhs, const Matrix& rhs);
	friend Vector operator*(const Matrix& lhs, const Point& rhs);
	friend Vector operator*(const Point& lhs, const Matrix& rhs);
	friend Vector operator*(const Matrix& lhs, const Vector& rhs);
	friend Vector operator*(const Vector& lhs, const Matrix& rhs);

	friend std::ostream& operator<<(std::ostream& os, const Matrix& m);
};

#endif
