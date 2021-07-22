#include "../../headers/engine/Scene.h"

#include <algorithm>

Scene::Scene() :
	_background({ 0, 0, 0 }),
	_ambient({ 1, 1, 1 })
{}

Scene::Scene(const Color& background, const Color& ambient) :
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

Scene& Scene::add(const std::shared_ptr<Object>& o) {
	this->_objects.push_back(o);
	return (*this);
}

Scene& Scene::add(const std::shared_ptr<Light>& l) {
	this->_lights.push_back(l);
	return (*this);
}

std::shared_ptr<Object> Scene::closestIntersected(const Ray& ray, Point& impact) const {
	float minDistance = FLT_MAX;
	float distance;
	Point p;
	std::shared_ptr<Object> closest = nullptr;

	for (const auto o : this->_objects)
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

std::list<std::shared_ptr<Object>> Scene::getObjects() const {
	return this->_objects;
}

std::list<std::shared_ptr<Light>> Scene::getLights() const {
	return this->_lights;
}

Color Scene::getBackground() const {
	return this->_background;
}

Color Scene::getAmbient() const {
	return this->_ambient;
}

std::ostream& operator<<(std::ostream& os, const Scene& s) {
	return os;
}
