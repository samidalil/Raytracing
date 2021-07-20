#include "../../headers/engine/Camera.h"
#include "../../headers/math/Point.h"

Camera::Camera() : Entity(), _focal(3) {}

Camera::Camera(float focal) : Entity(), _focal(focal) {}

Camera::Camera(Vector position, Vector rotation) : Entity(position, rotation, 1), _focal(3) {}

Camera::Camera(float focal, Vector position, Vector rotation) : Entity(position, rotation, 1), _focal(focal) {}

Ray Camera::getRay(float x, float y) const {
	const Point screenPos(x * 2 - 1, y * 2 - 1, 0);

	return this->localToGlobal(Ray(screenPos, screenPos - Point(0, 0, this->_focal))).normalized();
}
