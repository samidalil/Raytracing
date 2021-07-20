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

Scene::Scene(const Scene& s) {
	this->copy(s);
}

Scene& Scene::operator=(const Scene& s) {
	this->copy(s);
	return (*this);
}

void Scene::copy(const Scene& s) {
	this->_objects = s._objects;
	this->_lights = s._lights;
	this->_background = s._background;
	this->_ambient = s._ambient;
}

Object* Scene::closestIntersected(const Ray& ray, Point& impact) const {
	float minDistance = FLT_MAX;
	float distance;
	Point p;
	Object* closest = nullptr;

	for (Object* o : this->_objects)
		if (o->intersect(ray, p)) {
			distance = Vector(ray.origin - p).norm();

			if (distance < minDistance) {
				minDistance = distance;
				closest = o;
				impact = p;
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
