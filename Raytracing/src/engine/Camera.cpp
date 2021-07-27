#include "../../headers/engine/Camera.h"
#include "../../headers/math/Point.h"

Camera::Camera() : Entity(), _focal(3), _skybox(NULL) {}

Camera::Camera(float focal) : Entity(), _focal(focal), _skybox(NULL) {}

Camera::Camera(Vector position, Vector rotation) : Entity(position, rotation, 1), _focal(3), _skybox(NULL) {}

Camera::Camera(float focal, Vector position, Vector rotation) : Entity(position, rotation, 1), _focal(focal), _skybox(NULL) {}

Camera::Camera(const Camera& c) {
	this->copy(c);
}

Camera& Camera::operator=(const Camera& c) {
	this->copy(c);
	return (*this);
}

void Camera::copy(const Camera& c) {
	Entity::copy(c);
	this->_focal = c._focal;
}

std::string Camera::type() const
{
	return "\"Camera\"";
}

Ray Camera::getRay(float x, float y) const {
	const Point screenPos(x * 2 - 1, y * 2 - 1, 0);

	return this->localToGlobal(Ray(screenPos, screenPos - Point(0, 0, this->_focal))).normalized();
}

void Camera::setSkybox(std::shared_ptr<Material> material)
{
	this->_skybox = &Skybox(localToGlobal(Point()), 10.f, material);
}
