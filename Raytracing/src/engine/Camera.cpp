#include "../../headers/engine/Camera.h"
#include "../../headers/math/Point.h"

Camera::Camera() : Entity(), _focal(3)
{
	this->_skybox = std::make_shared<Sphere>(this->localToGlobal(Point(0, 0, this->_focal)), Vector(), abs(this->_focal) * 20.0f, nullptr);
}

Camera::Camera(float focal) : Entity(), _focal(focal)
{
	this->_skybox = std::make_shared<Sphere>(this->localToGlobal(Point(0, 0, this->_focal)), Vector(), abs(this->_focal) * 20.0f, nullptr);
}

Camera::Camera(Vector position, Vector rotation) : Entity(position, rotation, 1), _focal(3)
{
	this->_skybox = std::make_shared<Sphere>(this->localToGlobal(Point(0, 0, this->_focal)), Vector(), abs(this->_focal) * 20.0f, nullptr);
}

Camera::Camera(float focal, Vector position, Vector rotation) : Entity(position, rotation, 1), _focal(focal)
{
	this->_skybox = std::make_shared<Sphere>(this->localToGlobal(Point(0, 0, this->_focal)), Vector(), abs(this->_focal) * 20.0f, nullptr);
}

std::string Camera::type() const
{
	return "\"Camera\"";
}

Ray Camera::getRay(float x, float y) const {
	const Point screenPos(x * 2 - 1, y * 2 - 1, 0);

	return this->localToGlobal(Ray(screenPos, screenPos - Point(0, 0, this->_focal))).normalized();
}

void Camera::setSkybox(const std::shared_ptr<Material>& material)
{
	this->_skybox->setMaterial(material);
}

Color Camera::getSkyboxColor(const Ray& ray)
{
	Point impact;
	this->_skybox->intersect(ray, impact);
	return 	this->_skybox->getMaterial(impact).kd;
}
