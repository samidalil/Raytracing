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
	_tabCount = 0;
	file.open("E:\\dev\\Raytracing\\anotherTest.txt");
	file << tabulate() <<"{" << std::endl;
	_tabCount++;
	file << tabulate() << "\"textures:\": [" << std::endl;
	_tabCount++;
	for each (auto path in scene->getTexturePaths())
	{
		file << tabulate() << "\"" << path << "\"," << std::endl;
	}
	_tabCount--;
	file << tabulate() << "]," << std::endl;
	file << tabulate() << "materials: [" << std::endl;
	_tabCount++;
	file << tabulate() << "{" << std::endl;

	/*for each (auto obj in _objects)
	{
		file << typeid(obj).name()<<std::endl;
	}*/
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
