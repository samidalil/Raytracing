#ifndef RT_COLOR_H
#define RT_COLOR_H

class Color {
private:
	// Tableau contenant les valeurs x, y et z
	float _tab[3];

	void copy(const Color& p);
public:
	static Color black;
	static Color white;
	static Color red;
	static Color green;
	static Color blue;

	Color();
	Color(float r, float g, float b);
	Color(const Color& c);
	Color& operator=(const Color& c);

	float& operator[](int index);
	float operator[](int index) const;

	Color& operator+=(const Color& c);

	friend Color operator*(const Color& lhs, const Color& rhs);
	friend Color operator+(const Color& lhs, const Color& rhs);
	friend Color operator*(const Color& lhs, const float& rhs);
	friend Color operator*(const float& lhs, const Color& rhs);
};

#endif
