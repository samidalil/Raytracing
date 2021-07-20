#include <iostream>
#include <memory>

#include "headers/Constants.h"
#include "headers/image/Image.h"
#include "headers/primitives/Sphere.h"
#include "headers/engine/Light.h"
#include "headers/engine/Camera.h"
#include "headers/engine/Scene.h"
#include "headers/engine/Renderer.h"

int main()
{
	Scene scene(
		{
			new Sphere({ 0, 0, -5 }, { 0, 0, 0 }, 1),
			new Sphere({ 1.75, 2, -17 }, { 0, 0, 0 }, 1)
		},
		{
			new Light({ 50, 5, 0 }, {}, { 1, 1, 1 }, { 0.6, 0.6, 0.6 })
		},
		{ 0.3, 0.3, 0.3 },
		{ 0.2, 0.2, 0.2 }
	);
	Camera camera(10);
	Renderer renderer(800, 800);
	Image image = renderer.render(scene, camera);

	image.save(projectDir + "result.jpg");
	return 0;
}
