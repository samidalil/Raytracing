#include <iostream>
#include <memory>

#include "headers/Constants.h"
#include "headers/image/Image.h"
#include "headers/engine/Entity.h"

int main()
{
	Image image(800, 800, 3);
	Vector pos;
	Vector rot;
	float sca = 1;
	auto e = std::make_shared<Entity>(pos * 3, rot, sca);

	std::cout << *e << std::endl;
	
	//image.save(projectDir + "result.jpg");

	return 0;
}
