#ifndef RT_CAMERA_H
#define RT_CAMERA_H

#include "Entity.h"
#include "Ray.h"
#include "../math/Vector.h"

class Camera : public Entity {
private:
	float _focal;
public:
	Camera();
	Camera(float focal);
	Camera(Vector position, Vector rotation);
	Camera(float focal, Vector position, Vector rotation);

	Ray getRay(float x, float y) const;
};

#endif
