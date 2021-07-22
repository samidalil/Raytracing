#ifndef RT_RENDERER_H
#define RT_RENDERER_H

#include "Scene.h"
#include "Camera.h"
#include "../image/Image.h"

enum class Illumination{UNLIT, LAMBERT, PHONG };
class Renderer {
private:
	int _width;
	int _height;
	Illumination _illumination;
public:
	Renderer(int width, int height);

	Image render(const Scene& s, const Camera& c) const;
	Renderer& setIlluminationModel(const Illumination& illu);
};

#endif