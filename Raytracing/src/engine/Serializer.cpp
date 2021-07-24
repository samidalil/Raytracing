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
	for each (auto path in scene->getTexturePaths())
	{
		file << "{ ";
		file << "\"path\":" << "\"" << path.second << "\", "; //remove last coma? 
		file << "\"id\"" << path.first;
		file << "},";
	}
	file << "],";
	file << "\"materials\": [";
	for each (auto mat in scene->getMaterials())
	{
		file << "{ ";
		file << "\"ka\": " << mat->ka << ",";
		file << "\"kd\": " << mat->kd << ",";
		file << "\"ks\": " << mat->ks << ",";
		file << "\"shininess\": " << mat->shininess << ",";
		file << "\"texture\": " <<  mat->texture<< ","; //TODO
		file << "} ";
	}
	file << "],";
	file << "\"objects:\" [";
	for each (auto obj in scene->getObjects())
	{
		file << "{ ";
		//file << "\"type\": " << mat->ka << ","; //TODO
		file << "\"type\": " << ;


	}
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
