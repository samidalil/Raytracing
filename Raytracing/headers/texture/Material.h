#ifndef RT_MATERIAL_H
#define RT_MATERIAL_H

#include "Color.h"

class Material {
public:
	Color ka;
	Color kd;
	Color ks;
	float shininess;

	Material(Color ambient, Color diffuse, Color specular, float shininess);
	Material(const Material& m);
};

#endif
