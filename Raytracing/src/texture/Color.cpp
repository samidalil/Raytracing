#include "../../headers/texture/Color.h"

template <typename T>
T clamp(T v, T min, T max) {
	if (v < min) return min;
	if (v > max) return max;
	return v;
}

Color Color::black(0, 0, 0);
Color Color::white(1, 1, 1);
Color Color::red(1, 0, 0);
Color Color::green(0, 1, 0);
Color Color::blue(0, 0, 1);

Color::Color() {
	this->_tab[0] = 0;
	this->_tab[1] = 0;
	this->_tab[2] = 0;
}

Color::Color(float r, float g, float b) {
	this->_tab[0] = r;
	this->_tab[1] = g;
	this->_tab[2] = b;
}

Color::Color(const nlohmann::json tab)
{
	this->_tab[0] = tab[0];
	this->_tab[1] = tab[1];
	this->_tab[2] = tab[2];
}

float& Color::operator[](int index) {
	return this->_tab[index];
}

float Color::operator[](int index) const {
	return this->_tab[index];
}

Color& Color::operator+=(const Color& c) {
	this->_tab[0] = clamp(this->_tab[0] + c[0], 0.0f, 1.0f);
	this->_tab[1] = clamp(this->_tab[1] + c[1], 0.0f, 1.0f);
	this->_tab[2] = clamp(this->_tab[2] + c[2], 0.0f, 1.0f);
	return (*this);
}

Color operator*(const Color& lhs, const Color& rhs) {
	Color c;

	c[0] = clamp(lhs[0] * rhs[0], 0.0f, 1.0f);
	c[1] = clamp(lhs[1] * rhs[1], 0.0f, 1.0f);
	c[2] = clamp(lhs[2] * rhs[2], 0.0f, 1.0f);

	return c;
}

Color operator+(const Color& lhs, const Color& rhs)
{
	Color c;

	c[0] = clamp(lhs[0] + rhs[0], 0.0f, 1.0f);
	c[1] = clamp(lhs[1] + rhs[1], 0.0f, 1.0f);
	c[2] = clamp(lhs[2] + rhs[2], 0.0f, 1.0f);

	return c;
}

Color operator*(const Color& lhs, const float& rhs) {
	Color c;

	c[0] = clamp(lhs[0] * rhs, 0.0f, 1.0f);
	c[1] = clamp(lhs[1] * rhs, 0.0f, 1.0f);
	c[2] = clamp(lhs[2] * rhs, 0.0f, 1.0f);
	
	return c;
}

Color operator*(const float& lhs, const Color& rhs) {
	return rhs * lhs;
}

std::ostream& operator<<(std::ostream& os, const Color& c)
{
	os << "[" << c[0] << "," << c[1] << "," << c[2] << "]";
	return os;
}
