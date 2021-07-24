#ifndef RT_SERIALIZER_H
#define RT_SERIALIZER_H

#include <list>
#include <iostream>
#include "Scene.h"
#include <fstream>

class Serializer {
private:
	int _tabCount;
public:
	Serializer();
	Serializer(const Scene& scene);

	void serializeScene(const std::shared_ptr<Scene>& scene);
	Scene deserializeScene(const std::string& sceneFilePath) const;
	std::string tabulate() const;
};

#endif
