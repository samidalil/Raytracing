#ifndef RT_SCENE_H
#define RT_SCENE_H

#include <list>
#include <iostream>
#include "Object.h"
#include "Ray.h"
#include "Light.h"
#include <map>
#include "../math/Point.h"
#include "../texture/Color.h"
#include "../texture/Material.h"

class Scene {
private:
	std::list<std::shared_ptr<Object>> _objects;
	std::list<std::shared_ptr<Light>> _lights;
	std::list <std::shared_ptr<Material>>_materials;
	std::map<int,std::string> _texturePaths;

	Color _background;
	Color _ambient;
public:
	Scene();
	Scene(const Color& background, const Color& ambient);

	std::list<std::shared_ptr<Object>> getObjects() const;
	std::list<std::shared_ptr<Light>> getLights() const;
	std::list<std::shared_ptr<Material>> getMaterials() const;
	std::map<int, std::string> getTexturePaths() const;
	Color getBackground() const;
	Color getAmbient() const;

	Scene& add(const std::shared_ptr<Object>& o);
	Scene& add(const std::shared_ptr<Light>& l);
	Scene& add(const std::shared_ptr<Material>& m);
	Scene& add(const int id, const std::string& s);
	std::shared_ptr<Object> closestIntersected(const Ray& ray, Point& impact) const;

	friend std::ostream& operator<<(std::ostream& os, const Scene& s);
};

#endif
