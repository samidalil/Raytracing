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
	for(auto it = textures.begin(); it != textures.end();
		++it) {
		file << "{ ";
		file << **it;
		if (std::next(it) != textures.end()) //checks if last element
		{
			file << "},";
		}
		else
		{
			file << "}";
		}
	}
	file << "],";
	file << "\"materials\": [";
	auto materials = scene->getMaterials();
	for(auto it = materials.begin(); it != materials.end(); ++it)
	{
		file << "{ ";
		file << **it;
		if (std::next(it) != materials.end()) 
		{
			file << "},";
		}
		else
		{
			file << "}";
		}
	}
	file << "],";
	file << "\"objects\": [";
	auto objects = scene->getObjects();
	for (auto it = objects.begin(); it != objects.end(); ++it)
	{
		file << "{ ";
		file << **it;
		if (std::next(it) != objects.end())
		{
			file << "},";
		}
		else
		{
			file << "}";
		}
	}
	file << "],";
	file << "\"backgroundColor\": " << scene->getBackground() << ",";
	file << "\"ambientColor\": " << scene->getAmbient();
	file << "}";
	file.close();
}

Scene Serializer::deserializeScene(const std::string& sceneFilePath) const
{
	std::cout << "is clean file:" << checkFileFormat(sceneFilePath);
	return Scene();
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

std::string Serializer::cleanFileContent(const std::string& sceneFilePath) const
{
	std::string res = "";
	std::ifstream file;

	file.open(sceneFilePath, std::ifstream::in);
	char c = file.get();
	while (file.good())
	{
		if (c == '(' || c == '[' || c == '{')
			res.push_back(c);
		if (c == ')' || c == ']' || c == '}')
			res.push_back(c);
		c = file.get();
	}
	file.close();
	return res;
}

bool Serializer::checkFileFormat(const std::string& sceneFilePath) const
{
	//appeler clenafile content ici pour récupérer une string nettoyé 
	std::string cleanedString = cleanFileContent(sceneFilePath);
	std::cout << "cleaned file is: " << cleanedString;
	std::stack<char> FILO;
	for (auto c : cleanedString)
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
	}
	return FILO.empty();
}
