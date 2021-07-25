#include "../../headers/engine/Serializer.h"

Serializer::Serializer()
{
}

Serializer::Serializer(const std::string& write, const std::string& read)
	: pathToWrite(write), pathToRead(read) {}

void Serializer::serializeScene(const std::shared_ptr<Scene>& scene)
{
	std::ofstream file;
	file.open(pathToWrite);
	file << "{";
	file << "\"textures\": [";
	auto textures = scene->getTextures();
	//TODO do iterator and check if = to end()
	
	//						v dangling pointer 
	for (auto it = textures.begin(); it != textures.end();
		++it) {
		file << "{ ";
		file << *it;
		if (std::next(it) != scene->getTextures().end()) //checks if last element
		{
			file << "},";
		}
		else
		{
			file << "}";
		}
	}/*
	for(auto texture : scene->getTextures())
	{
		file << "{ ";
		file << *texture;
		file << "},";
	}*/
	file << "],";
	file << "\"materials\": [";
	for(auto mat : scene->getMaterials())
	{
		file << "{ ";
		file << *mat;
		file << "}, ";
	}
	file << "],";
	file << "\"objects:\" [";

	for(auto obj : scene->getObjects())
	{
		file << "{ ";
		file << *obj;
		file << "},";
	}
	file << "\"backgroundColor\": " << scene->getBackground() << ",";
	file << "\"ambientColor\": " << scene->getAmbient();
	file << "}";
	file.close();
}

Scene Serializer::deserializeScene(const std::string& sceneFilePath) const
{
	//base to read a file and prints it in console
	std::ifstream file;
	file.open(sceneFilePath, std::ifstream::in);
	
	char c = file.get();
	while (file.good())
	{
		std::cout << c;
		c = file.get();
	}
	file.close();

	return Scene();
}

bool Serializer::checkFileFormat(const std::string& sceneFilePath) const
{
	std::ifstream file;
	file.open(sceneFilePath, std::ifstream::in);
	char c = file.get();
	std::stack<char> FILO;
	if (!file.good()) 
	{
		file.close();
		return false;
	}
	while (file.good())
	{
		switch (c) {
		case '(':
			FILO.push(')');
			break;
		case '[':
			FILO.push(']');
			break;
		case '{':
			FILO.push('}');
			break;
		default:
			if (FILO.empty())return false;
			if (FILO.top() != c)return false;
			FILO.pop();
			break;
		}
		c = file.get();
	}
	file.close();
	return FILO.empty();
	return false;
}
