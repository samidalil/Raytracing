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
	Illumination _illuminationModel;

public:
	Renderer(int width, int height);

	Image render(Scene s, Camera c) const;
	void setIlluminationModel(Illumination illu);
};

#endif