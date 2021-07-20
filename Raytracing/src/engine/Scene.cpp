#include "../../headers/engine/Scene.h"

Scene::Scene(const std::list<Object*>& objects, const std::list<Light*>& lights) :
	_objects(objects),
	_lights(lights),
	_background({ 0, 0, 0 }),
	_ambient({ 1, 1, 1 })
{}

Scene::Scene(const std::list<Object*>& objects, const std::list<Light*>& lights, Color background, Color ambient) :
	_objects(objects),
	_lights(lights),
	_background(background),
	_ambient(ambient)
{}

Object* Scene::closestIntersected(const Ray& ray, Point& impact) const {
	float minDistance = FLT_MAX;
	float distance;
	Object* closest = nullptr;

	for (Object* object : this->_objects)
		if (object->intersect(ray, impact)) {
			distance = Vector(ray.origin - impact).norm();

			if (distance < minDistance) {
				minDistance = distance;
				closest = object;
			}
		}

	return closest;
}

std::list<Light*> Scene::getLights() const {
	return this->_lights;
}

Color Scene::getBackground() const {
	return this->_background;
}

Color Scene::getAmbient() const {
	return this->_ambient;
}
