#include "../../headers/math/Matrix.h"

Matrix::Matrix() {
	for (int i = 0; i < 16; ++i) this->_tab[i] = i % 4 == i / 4;
}

Matrix::Matrix(const nlohmann::json tab)
{
	for (int i = 0; i < 16; ++i) this->_tab[i] = tab[i];
}

Matrix::Matrix(const Matrix& m) {
	copy(m);
}

Matrix& Matrix::operator=(const Matrix& m) {
	copy(m);
	return (*this);
}

void Matrix::copy(const Matrix& m) {
	for (int i = 0; i < 16; ++i) this->_tab[i] = m._tab[i];
}

Matrix Matrix::inverse() const {
	const Matrix& a = *this;
	Matrix m;

	m(0, 0) = a(1, 1) * a(2, 2) * a(3, 3)
		+ a(1, 2) * a(2, 3) * a(3, 1)
		+ a(1, 3) * a(2, 1) * a(3, 2)
		- a(1, 3) * a(2, 2) * a(3, 1)
		- a(1, 2) * a(2, 1) * a(3, 3)
		- a(1, 1) * a(2, 3) * a(3, 2);

	m(0, 1) = -a(0, 1) * a(2, 2) * a(3, 3)
		- a(0, 2) * a(2, 3) * a(3, 1)
		- a(0, 3) * a(2, 1) * a(3, 2)
		+ a(0, 3) * a(2, 2) * a(3, 1)
		+ a(0, 2) * a(2, 1) * a(3, 3)
		+ a(0, 1) * a(2, 3) * a(3, 2);

	m(0, 2) = a(0, 1) * a(1, 2) * a(3, 3)
		+ a(0, 2) * a(1, 3) * a(3, 1)
		+ a(0, 3) * a(1, 1) * a(3, 2)
		- a(0, 3) * a(1, 2) * a(3, 1)
		- a(0, 2) * a(1, 1) * a(3, 3)
		- a(0, 1) * a(1, 3) * a(3, 2);

	m(0, 3) = -a(0, 1) * a(1, 2) * a(2, 3)
		- a(0, 2) * a(1, 3) * a(2, 1)
		- a(0, 3) * a(1, 1) * a(2, 2)
		+ a(0, 3) * a(1, 2) * a(2, 1)
		+ a(0, 2) * a(1, 1) * a(2, 3)
		+ a(0, 1) * a(1, 3) * a(2, 2);

	m(1, 0) = -a(1, 0) * a(2, 2) * a(3, 3)
		- a(1, 2) * a(2, 3) * a(3, 0)
		- a(1, 3) * a(2, 0) * a(3, 2)
		+ a(1, 3) * a(2, 2) * a(3, 0)
		+ a(1, 2) * a(2, 0) * a(3, 3)
		+ a(1, 0) * a(2, 3) * a(3, 2);

	m(1, 1) = a(0, 0) * a(2, 2) * a(3, 3)
		+ a(0, 2) * a(2, 3) * a(3, 0)
		+ a(0, 3) * a(2, 0) * a(3, 2)
		- a(0, 3) * a(2, 2) * a(3, 0)
		- a(0, 2) * a(2, 0) * a(3, 3)
		- a(0, 0) * a(2, 3) * a(3, 2);

	m(1, 2) = -a(0, 0) * a(1, 2) * a(3, 3)
		- a(0, 2) * a(1, 3) * a(3, 0)
		- a(0, 3) * a(1, 0) * a(3, 2)
		+ a(0, 3) * a(1, 2) * a(3, 0)
		+ a(0, 2) * a(1, 0) * a(3, 3)
		+ a(0, 0) * a(1, 3) * a(3, 2);

	m(1, 3) = a(0, 0) * a(1, 2) * a(2, 3)
		+ a(0, 2) * a(1, 3) * a(2, 0)
		+ a(0, 3) * a(1, 0) * a(2, 2)
		- a(0, 3) * a(1, 2) * a(2, 0)
		- a(0, 2) * a(1, 0) * a(2, 3)
		- a(0, 0) * a(1, 3) * a(2, 2);

	m(2, 0) = a(1, 0) * a(2, 1) * a(3, 3)
		+ a(1, 1) * a(2, 3) * a(3, 0)
		+ a(1, 3) * a(2, 0) * a(3, 1)
		- a(1, 3) * a(2, 1) * a(3, 0)
		- a(1, 1) * a(2, 0) * a(3, 3)
		- a(1, 0) * a(2, 3) * a(3, 1);

	m(2, 1) = -a(0, 0) * a(2, 1) * a(3, 3)
		- a(0, 1) * a(2, 3) * a(3, 0)
		- a(0, 3) * a(2, 0) * a(3, 1)
		+ a(0, 3) * a(2, 1) * a(3, 0)
		+ a(0, 1) * a(2, 0) * a(3, 3)
		+ a(0, 0) * a(2, 3) * a(3, 1);

	m(2, 2) = a(0, 0) * a(1, 1) * a(3, 3)
		+ a(0, 1) * a(1, 3) * a(3, 0)
		+ a(0, 3) * a(1, 0) * a(3, 1)
		- a(0, 3) * a(1, 1) * a(3, 0)
		- a(0, 1) * a(1, 0) * a(3, 3)
		- a(0, 0) * a(1, 3) * a(3, 1);

	m(2, 3) = -a(0, 0) * a(1, 1) * a(2, 3)
		- a(0, 1) * a(1, 3) * a(2, 0)
		- a(0, 3) * a(1, 0) * a(2, 1)
		+ a(0, 3) * a(1, 1) * a(2, 0)
		+ a(0, 1) * a(1, 0) * a(2, 3)
		+ a(0, 0) * a(1, 3) * a(2, 1);

	m(3, 0) = -a(1, 0) * a(2, 1) * a(3, 2)
		- a(1, 1) * a(2, 2) * a(3, 0)
		- a(1, 2) * a(2, 0) * a(3, 1)
		+ a(1, 2) * a(2, 1) * a(3, 0)
		+ a(1, 1) * a(2, 0) * a(3, 2)
		+ a(1, 0) * a(2, 2) * a(3, 1);

	m(3, 1) = a(0, 0) * a(2, 1) * a(3, 2)
		+ a(0, 1) * a(2, 2) * a(3, 0)
		+ a(0, 2) * a(2, 0) * a(3, 1)
		- a(0, 2) * a(2, 1) * a(3, 0)
		- a(0, 1) * a(2, 0) * a(3, 2)
		- a(0, 0) * a(2, 2) * a(3, 1);

	m(3, 2) = -a(0, 0) * a(1, 1) * a(3, 2)
		- a(0, 1) * a(1, 2) * a(3, 0)
		- a(0, 2) * a(1, 0) * a(3, 1)
		+ a(0, 2) * a(1, 1) * a(3, 0)
		+ a(0, 1) * a(1, 0) * a(3, 2)
		+ a(0, 0) * a(1, 2) * a(3, 1);

	m(3, 3) = a(0, 0) * a(1, 1) * a(2, 2)
		+ a(0, 1) * a(1, 2) * a(2, 0)
		+ a(0, 2) * a(1, 0) * a(2, 1)
		- a(0, 2) * a(1, 1) * a(2, 0)
		- a(0, 1) * a(1, 0) * a(2, 2)
		- a(0, 0) * a(1, 2) * a(2, 1);

	const float det = a(0, 0) * m(0, 0)
		+ a(1, 0) * m(0, 1)
		+ a(2, 0) * m(0, 2)
		+ a(3, 0) * m(0, 3);

	if (det == 0) return Matrix();

	for (int i = 0; i < 16; ++i) m._tab[i] /= det;

	return m;
}

float& Matrix::operator()(int x, int y) {
	return this->_tab[x * 4 + y];
}

float Matrix::operator()(int x, int y) const {
	return this->_tab[x * 4 + y];
}

Matrix operator*(const Matrix& lhs, const Matrix& rhs) {
	Matrix m;

	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			m(i, j) = rhs(0, j) * lhs(i, 0) + rhs(1, j) * lhs(i, 1) + rhs(2, j) * lhs(i, 2) + rhs(3, j) * lhs(i, 3);

	return m;
}

Point operator*(const Matrix& lhs, const Point& rhs) {
	Point v;

	for (int i = 0; i < 3; ++i)
		v[i] = lhs(i, 0) * rhs[0] + lhs(i, 1) * rhs[1] + lhs(i, 2) * rhs[2] + lhs(i, 3);

	return v;
}

Point operator*(const Point& lhs, const Matrix& rhs) {
	Point v;

	for (int i = 0; i < 3; ++i)
		v[i] = lhs[0] * rhs(0, i) + lhs[1] * rhs(1, i) + lhs[2] * rhs(2, i) + rhs(3, i);

	return v;
}

Vector operator*(const Matrix& lhs, const Vector& rhs) {
	Vector v;

	for (int i = 0; i < 3; ++i)
		v[i] = lhs(i, 0) * rhs[0] + lhs(i, 1) * rhs[1] + lhs(i, 2) * rhs[2];

	return v;
}

Vector operator*(const Vector& lhs, const Matrix& rhs) {
	Vector v;

	for (int i = 0; i < 3; ++i)
		v[i] = lhs[0] * rhs(0, i) + lhs[1] * rhs(1, i) + lhs[2] * rhs(2, i);

	return v;
}

std::ostream& operator<<(std::ostream& os, const Matrix& m) {
	
	/* Debug implementation of << operator 
	for (int i = 0; i < 3; ++i) {
		os << "| ";
		for (int j = 0; j < 3; ++j) os << m(i, j) << ", ";
		os << m(i, 3) << " |" << std::endl;
	}
	os << "| ";
	for (int j = 0; j < 3; ++j) os << m(3, j) << ", ";
	os << m(3, 3) << " |";

	return os;*/
	os << "[";
	for (int i = 0; i < 16; ++i)
	{
		os << m._tab[i];
		if (i != 15)
			os << ",";
	}
	os << "]";
	return os;
}
