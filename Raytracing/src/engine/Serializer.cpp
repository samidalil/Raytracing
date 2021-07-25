#include "../../headers/engine/Serializer.h"

Serializer::Serializer()
{
}

Serializer::Serializer(const Scene& scene)
{
}

void Serializer::serializeScene(const std::shared_ptr<Scene>& scene)
{
	std::ofstream file;
	file.open("E:\\dev\\Raytracing\\anotherTest.txt");
	file << "{";
	file << "\"textures:\": [";
	
	//TODO do iterator and check if = to end()
	for(auto texture : scene->getTextures())
	{
		file << "{ ";
		file << *texture;
		file << "},";
	}
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
	file << "\"backgroundColor\": \"" << scene->getBackground() << "\"";
	file << "\"ambientColor\": \"" << scene->getAmbient() << "\"";
	file.close();
}

std::string Serializer::tabulate() const
{
	std::string res = "";
	for (int i = 0; i < _tabCount; i++)
	{
		res += "\t";
	}

	return res;
}
