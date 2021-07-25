#ifndef RT_COLOR_H
#define RT_COLOR_H

#include <iostream>
#include "../../vendor/json/single_include/nlohmann/json.hpp"

class Color {
private:
	// Tableau contenant les valeurs x, y et z
	float _tab[3];
public:
	static Color black;
	static Color white;
	static Color red;
	static Color green;
	static Color blue;

	Color();
	Color(float r, float g, float b);
	Color(const nlohmann::json tab);

	float& operator[](int index);
	float operator[](int index) const;

	Color& operator+=(const Color& c);

	friend Color operator*(const Color& lhs, const Color& rhs);
	friend Color operator+(const Color& lhs, const Color& rhs);
	friend Color operator*(const Color& lhs, const float& rhs);
	friend Color operator*(const float& lhs, const Color& rhs);

	friend std::ostream& operator<<(std::ostream& os, const Color& c);

};

#endif
