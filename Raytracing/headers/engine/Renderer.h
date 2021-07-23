#ifndef RT_RENDERER_H
#define RT_RENDERER_H

#include "Scene.h"
#include "Camera.h"
#include "../image/Image.h"

enum class Illumination {
	LAMBERT,
	PHONG
};

struct RendererProperties {
	bool enableShadows = true;
	int width = 800;
	int height = 800;
	int ssaaSubdivisions = 2;
	Illumination illumination = Illumination::PHONG;
	std::shared_ptr<Scene> scene;
	std::shared_ptr<Camera> camera;
};

class Renderer {
private:
	RendererProperties _properties;

	Color getImpactColorLambert(const Ray& r, const std::shared_ptr<Object>& obj, const Point& impact) const;
	Color getImpactColorPhong(const Ray& r, const std::shared_ptr<Object>& obj, const Point& impact) const;
public:
	Renderer() = default;
	Renderer(const RendererProperties& properties);

	Renderer& setProperties(const RendererProperties& properties);

	Image render() const;
};

#endif