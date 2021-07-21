#ifndef RT_MATERIAL_H
#define RT_MATERIAL_H

#include "Color.h"
#include "../image/Image.h"

class Material {
private:
	void copy(const Material& m);
public:
	Color ka;
	Color kd;
	Color ks;
	float shininess;

	Material();
	Material(Color ambient, Color diffuse, Color specular, float shininess);
	Material(const Material& m);
	Material& operator=(const Material& m);
};

#endif
