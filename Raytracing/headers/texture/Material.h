#ifndef RT_MATERIAL_H
#define RT_MATERIAL_H

#include <memory>
#include "Color.h"
#include "Texture.h"
#include "../math/Point.h"

class Material {
private:
	void copy(const Material& m);
public:
	Color ka;
	Color kd;
	Color ks;
	float shininess;
	Texture texture;
	

	Material();
	Material(Color ambient, Color diffuse, Color specular, float shininess);
	Material(const Material& m);
	Material& operator=(const Material& m);

	Material getColor(float x, float y) const;
	friend std::ostream& operator<<(std::ostream& os, const Material& m);
};

#endif
