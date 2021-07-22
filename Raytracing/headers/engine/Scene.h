#ifndef RT_SCENE_H
#define RT_SCENE_H

#include <list>
#include <iostream>
#include "Object.h"
#include "Ray.h"
#include "Light.h"
#include "../math/Point.h"
#include "../texture/Color.h"

class Scene {
private:
	std::list<std::shared_ptr<Object>> _objects;
	std::list<std::shared_ptr<Light>> _lights;
	Color _background;
	Color _ambient;

	void copy(const Scene& s);
public:
	Scene();
	Scene(const Color& background, const Color& ambient);
	Scene(const Scene& s);
	Scene& operator=(const Scene& s);

	std::list<std::shared_ptr<Object>> getObjects() const;
	std::list<std::shared_ptr<Light>> getLights() const;
	Color getBackground() const;
	Color getAmbient() const;

	Scene& add(const std::shared_ptr<Object>& o);
	Scene& add(const std::shared_ptr<Light>& l);
	std::shared_ptr<Object> closestIntersected(const Ray& ray, Point& impact) const;

	friend std::ostream& operator<<(std::ostream& os, const Scene& s);
};

#endif
