#ifndef RT_SERIALIZER_H
#define RT_SERIALIZER_H

#include <list>
#include <iostream>
#include <fstream>
#include <stack>

#include "Scene.h"

class Serializer {
private:
	std::string cleanFileContent(const std::string& sceneFilePath) const;
	bool checkFileFormat(const std::string& sceneFilePath) const;

public:
	std::string pathToWrite;
	std::string pathToRead;

	Serializer();
	Serializer(const std::string& writePath, const std::string& readPath);

	void serializeScene(const std::shared_ptr<Scene>& scene);
	Scene deserializeScene(const std::string& sceneFilePath) const;
};

#endif
