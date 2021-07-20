#ifndef RT_SCENE_H
#define RT_SCENE_H

#include <list>
#include "Object.h"
#include "Ray.h"
#include "Light.h"
#include "../math/Point.h"
#include "../texture/Color.h"

class Scene {
private:
	std::list<Object*> _objects;
	std::list<Light*> _lights;
	Color _background;
	Color _ambient;
public:
	Scene(const std::list<Object*>& objects, const std::list<Light*>& lights);
	Scene(const std::list<Object*>& objects, const std::list<Light*>& lights, Color background, Color ambient);

	Object* closestIntersected(const Ray& ray, Point& impact) const;

	std::list<Light*> getLights() const;

	Color getBackground() const;
	Color getAmbient() const;
};

#endif
