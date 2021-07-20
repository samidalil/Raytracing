#ifndef RT_RENDERER_H
#define RT_RENDERER_H

#include "Scene.h"
#include "Camera.h"
#include "../image/Image.h"

class Renderer {
private:
	int _width;
	int _height;
public:
	Renderer(int width, int height);

	Image render(Scene s, Camera c) const;
};

#endif