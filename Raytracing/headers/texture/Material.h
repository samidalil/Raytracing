#ifndef RT_MATERIAL_H
#define RT_MATERIAL_H

#include <memory>
#include "Color.h"
#include "../math/Point.h"
#include "../image/Image.h"

class Material {
private:
	void copy(const Material& m);
public:
	Color ka;
	Color kd;
	Color ks;
	float shininess;
	std::shared_ptr<Image> texture;

	Material();
	Material(Color ambient, Color diffuse, Color specular, float shininess);
	Material(const Material& m);
	Material& operator=(const Material& m);

	Material getColor(float x, float y) const;
};

#endif
