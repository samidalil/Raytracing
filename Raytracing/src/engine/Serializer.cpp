#include "../../headers/engine/Serializer.h"
#include "../../vendor/json/single_include/nlohmann/json.hpp"
#include "../../headers/primitives/Cube.h"
#include "../../headers/primitives/Sphere.h"
#include "../../headers/primitives/Cone.h"
#include "../../headers/primitives/Cylinder.h"
#include "../../headers/primitives/Square.h"
#include "../../headers/primitives/Triangle.h"
#include "../../headers/primitives/Plane.h"
#include "../../headers/lights/AmbientLight.h"
#include "../../headers/lights/PointLight.h"

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

	for (auto it = textures.begin(); it != textures.end();
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
	for (auto it = materials.begin(); it != materials.end(); ++it)
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
	file << "\"skyboxMaterial\": { " << *scene->skyboxMaterial << " },";
	file << "\"backgroundColor\": " << scene->getBackground() << ",";
	file << "\"ambientColor\": " << scene->getAmbient();
	file << "}";
	file.close();
}

std::shared_ptr<Scene> Serializer::deserializeScene(const std::string& sceneFilePath) const
{
	bool isFormated = checkFileFormat(sceneFilePath);
	if (!isFormated)
	{
		return nullptr;
	}

	std::ifstream file;
	file.open(sceneFilePath, std::ifstream::in);

	nlohmann::json js = nlohmann::json::parse(file);
	auto scene = std::make_shared<Scene>(js["backgroundColor"], js["ambientColor"]);

	for (auto& texture : js["textures"])
	{
		scene->add(std::make_shared<Texture>(
			std::string(texture["path"]),
			int(texture["id"])
			));
	}

	auto textures = scene->getTextures();
	for (auto& material : js["materials"])
	{
		auto mat = std::make_shared<Material>(
			int(material["id"]),
			Color(material["ka"]),
			Color(material["kd"]),
			Color(material["ks"]),
			float(material["shininess"])
			);

		if (material.find("texture") != material.end()) {
			auto textureId = int(material["texture"]);
			auto texture = std::find_if(textures.begin(), textures.end(),
				[textureId](const std::shared_ptr<Texture>& t) {
					return t->id == textureId;
				});


			if (texture != textures.end())
				mat->texture = *texture;
		}

		scene->add(mat);
	}

	auto materials = scene->getMaterials();
	for (auto& object : js["objects"])
	{
		std::shared_ptr<Object> o;
		const std::string typeStr = object["type"];
		const char* type = typeStr.c_str();

		if (std::strcmp(type, "Cube") == 0)
			o = std::make_shared<Cube>(Matrix(object["transform"]));
		else if (std::strcmp(type, "Sphere") == 0)
			o = std::make_shared<Sphere>(Matrix(object["transform"]));
		else if (std::strcmp(type, "Cone") == 0)
			o = std::make_shared<Cone>(Matrix(object["transform"]));
		else if (std::strcmp(type, "Cylinder") == 0)
			o = std::make_shared<Cylinder>(Matrix(object["transform"]));
		else if (std::strcmp(type, "Plane") == 0)
			o = std::make_shared<Plane>(Matrix(object["transform"]));
		else if (std::strcmp(type, "Square") == 0)
			o = std::make_shared<Square>(Matrix(object["transform"]));
		else if (std::strcmp(type, "Triangle") == 0)
			o = std::make_shared<Triangle>(Matrix(object["transform"]));

		if (object.find("material") != object.end()) {
			auto materialId = int(object["material"]);
			auto material = std::find_if(materials.begin(), materials.end(),
				[materialId](const std::shared_ptr<Material>& m) {
					return m->id == materialId;
				});

			if (material != materials.end())
				o->setMaterial(*material);
		}

		scene->add(o);
	}

	for (auto& light : js["lights"])
	{
		std::shared_ptr<Light> l;
		const std::string typeStr = light["type"];
		const char* type = typeStr.c_str();

		if (std::strcmp(type, "AmbientLight") == 0)
			l = std::make_shared<AmbientLight>(Matrix(light["transform"]), Color(light["id"]), Color(light["is"]), float(light["intensity"]));
		else if (std::strcmp(type, "PointLight") == 0)
			l = std::make_shared<PointLight>(Matrix(light["transform"]), Color(light["id"]), Color(light["is"]), float(light["intensity"]));

		scene->add(l);
	}

	auto& skyboxMaterial = js["skyboxMaterial"];

	auto mat = std::make_shared<Material>(
		int(skyboxMaterial["id"]),
		Color(skyboxMaterial["ka"]),
		Color(skyboxMaterial["kd"]),
		Color(skyboxMaterial["ks"]),
		float(skyboxMaterial["shininess"])
		);

	if (skyboxMaterial.find("texture") != skyboxMaterial.end()) {
		auto textureId = int(skyboxMaterial["texture"]);
		auto texture = std::find_if(textures.begin(), textures.end(),
			[textureId](const std::shared_ptr<Texture>& t) {
				return t->id == textureId;
			});


		if (texture != textures.end())
			mat->texture = *texture;

		scene->add(mat);

	}

	return scene;

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
