#ifndef RT_LIGHT_H
#define RT_LIGHT_H

#include "Entity.h";
#include "Ray.h";
#include "../math/Vector.h";
#include "../math/Point.h";
#include "../texture/Color.h"

class Light : public Entity {
public:
	Color id;
	Color is;

	Light(Color diffuse, Color specular);
	Light(Vector position, Vector rotation, Color diffuse, Color specular);
	
	Ray getRayToLight(const Point& p) const;
	Ray getRayFromLight(const Point& p) const;
	Vector getVectorToLight(const Point& p) const;
	Vector getVectorFromLight(const Point& p) const;
};

#endif
