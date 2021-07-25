#include "../../headers/engine/Serializer.h"
#include "../../vendor/json/single_include/nlohmann/json.hpp"

Serializer::Serializer()
{
}

Serializer::Serializer(const std::string& write, const std::string& read)
	: pathToWrite(write), pathToRead(read) {}

void Serializer::serializeScene(const std::shared_ptr<Scene>& scene)
{
	std::cout << pathToWrite;
	std::ofstream file;
	file.open(pathToWrite);
	file << "{";
	file << "\"textures\": [";
	auto textures = scene->getTextures();
	
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
	file << "\"lights\": [";
	auto lights = scene->getLights();
	for (auto it = lights.begin(); it != lights.end(); ++it)
	{
		file << "{ ";
		file << **it;
		if (std::next(it) != lights.end())
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
	bool isFormated = checkFileFormat(sceneFilePath);
	if (!isFormated)
	{
		return Scene();
	}

	std::cout << "BONJOUR";
	std::ifstream file;
	file.open(sceneFilePath, std::ifstream::in);

	nlohmann::json js = nlohmann::json::parse(file);
	auto scene = std::make_shared<Scene>();

	for(auto& texture : js["textures"])
	{
		scene->add(std::make_shared<Texture>(texture["path"],texture["id"]));
	}
	/*
	auto textures = scene->getTextures();
	for(auto& material : js["materials"])
	{
		auto mat = std::make_shared<Material>(material["id"], material["ka"], material["kd"], material["ks"], material["shininess"]);
		auto textureId = material["texture"];
		auto texture = std::find_if(textures.begin(), textures.end(), [textureId] 
		(const std::shared_ptr<Texture>& t)
			{
				return t->id == textureId;
			});
		if(texture != textures.end()) 
			mat->texture = *texture;
		scene->add(mat);
	}*/
	/*
	for (auto& object : js["objects"])
	{
		auto obj = std::make_shared<Object>(material["id"], material["ka"], material["kd"], material["ks"], material["shininess"]);
		auto textureId = material["texture"];
		auto texture = std::find_if(textures.begin(), textures.end(), [textureId]
		(const std::shared_ptr<Texture>& t)
			{
				return t->id == textureId;
			});
		if (texture != textures.end())
			mat->texture = *texture;
		scene->add(mat);
	}
	*/

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
