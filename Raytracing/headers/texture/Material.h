#ifndef RT_MATERIAL_H
#define RT_MATERIAL_H

#include <memory>
#include "Color.h"
#include "Texture.h"
#include "../math/Point.h"
#include "../helpers/IdGenerator.h"

class Material {
private:
	void copy(const Material& m);
	static IdGenerator idGenerator;
public:
	int id;
	Color ka;
	Color kd;
	Color ks;
	float shininess;
	std::shared_ptr<Texture> texture;
	

	Material();
	Material(Color ambient, Color diffuse, Color specular, float shininess);
	Material(const Material& m);
	Material& operator=(const Material& m);

	Material getColor(float x, float y) const;
	friend std::ostream& operator<<(std::ostream& os, const Material& m);
};

#endif
