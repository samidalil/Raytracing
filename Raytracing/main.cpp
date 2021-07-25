//------------------------------------------------------------------------\\
//                                                                        \\
//                                                                        \\
//                A very very very very very simple raytracer             \\
//                                                                        \\
//                                                                        \\
//                    ______             ______                           \\
//                    | ___ \           |___  /                           \\
//                    | |_/ /__ _ _   _    / /                            \\
//                    |    // _` | | | |  / /                             \\
//                    | |\ \ (_| | |_| |./ /___                           \\
//                    \_| \_\__,_|\__, |\_____/                           \\
//                                 __/ |                                  \\
//                                |___/                                   \\
//                                                                        \\
//                                by                                      \\
//                                                                        \\
//           Lior Diler, Sami Dalil and Tom Rakotomanampison              \\
//                            ESGI - 2021                                 \\
//                                                                        \\
//                                                                        \\
//------------------------------------------------------------------------\\

#include <iostream>
#include <memory>
#include <algorithm>

#include "headers/image/Image.h"
#include "headers/primitives/Sphere.h"
#include "headers/engine/Camera.h"
#include "headers/engine/Scene.h"
#include "headers/engine/Renderer.h"
#include "headers/texture/Material.h"
#include "headers/texture/Texture.h"
#include "headers/primitives/Plane.h"
#include "headers/primitives/Cube.h"
#include "headers/lights/AmbientLight.h"
#include "headers/lights/PointLight.h"
#include "headers/primitives/Square.h"
#include "headers/primitives/Cylinder.h"
#include "headers/primitives/Triangle.h"
#include "headers/primitives/Cone.h"
#include "headers/engine/Serializer.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "headers/ui/window.h"


struct DataContext {
	RendererProperties rendererProperties;
	Renderer renderer;
	std::string filename;
	std::string savePath;
};

void renderCallback(float w, float h, int ssaSub, bool shadowActivated, Illumination illuminationModel, std::string savePath, std::string fileName)
{
	auto texture = std::make_shared<Texture>("E:\\dev\\Raytracing\\resources\\sample.jpg");
	// prepare to render 
	auto material1 = std::make_shared<Material>(Color::white, Color::white, Color::white * 0.2, 1);
	auto material2 = std::make_shared<Material>(Color::white, Color::white, Color::white * 0.5, 1);
	material2->texture = *texture;
	auto blue = std::make_shared<Material>(Color(0, 0, 1), Color(0, 0, 1), Color(0, 0, 1), 1);
	auto red = std::make_shared<Material>(Color(1, 0, 0), Color(1, 0, 0), Color(1, 0, 0), 1);
	auto pos = Vector(-2, 2.4, -35);
	auto pos2 = Vector(1, 3.5, -25);
	//auto s1 = std::make_shared<Cube>(pos, Vector(0.2, 0.7, 0), 1.7, material2);
	auto ground = std::make_shared<Square>(Vector(0, -1.2, -11), Vector(90, 0, 0), 2, material1);
	auto plane = std::make_shared<Plane>(Vector(0, 0, -50), Vector(0, 90, 0), 2, blue);
	auto leftWall = std::make_shared<Square>(Vector(-2.1, 0, -10), Vector(0, 80, 0), 3, red);
	auto rightWall = std::make_shared<Square>(Vector(2.1, 0, -10), Vector(0, -80, 0), 3, red);
	auto s2 = std::make_shared<Sphere>(Vector(0, 0, 0 - 11), Vector(), .4f, material2);
	auto cone = std::make_shared<Cone>(Vector(0, 0, 0 - 15), Vector(0,90,0), .1f, blue);
	auto cy1 = std::make_shared<Cylinder>(Vector(0, 2, -15), Vector(0., 0.5, 1), 0.5, material2);
	auto t1 = std::make_shared<Triangle>(Vector(-1, 0, -20), Vector(90, 0, 0), 1.7, material1);
	auto l1 = std::make_shared<PointLight>(Vector(0.2f, 0, -9), Vector(0, 0, 0), Color(1, 0, 0), Color::white * 0.4f, 1.f);
	auto l2 = std::make_shared<AmbientLight>(Vector(-0.2f, -0.7, -10), Vector(0, 0, 0), Color(0, 0, 1), Color::white * 0.4f, 1.f);
	auto scene = std::make_shared<Scene>(Color::blue * 0.1 + Color::red * 0.15, Color::white * 0.4);
	auto camera = std::make_shared<Camera>(10);

	scene->add(texture);
	//scene->add(material2->_id.count(),material2->texture);
	scene->add(material1);
	scene->add(material2);
	scene->add(s2);
	scene->add(plane);
	scene->add(leftWall);
	scene->add(rightWall);*/
	scene->add(l1);
	std::string pathWrite = "E:\\dev\\Raytracing\\SerializedData.txt";
	std::string pathRead = "E:\\dev\\Raytracing\\sampleScene.txt";
	Serializer serializer(pathWrite, pathRead);
	scene->add(l2);
	scene->add(ground);


	auto serializer = Serializer();
	serializer.serializeScene(scene);
	serializer.deserializeScene(pathWrite);
	std::cout << "format file is: " << serializer.checkFileFormat("E:\\dev\\Raytracing\\test1.txt") << std::endl;
	std::cout << "format file is: " << serializer.checkFileFormat("E:\\dev\\Raytracing\\test2.txt") << std::endl;
	std::cout << "format file is: " << serializer.checkFileFormat(pathWrite) << std::endl;
	DataContext data;

	data.rendererProperties.scene = scene;
	data.rendererProperties.camera = camera;
	data.rendererProperties.ssaaSubdivisions = ssaSub;
	data.rendererProperties.width = w;
	data.rendererProperties.height = h;
	data.rendererProperties.illumination = illuminationModel;
	data.rendererProperties.enableShadows = shadowActivated;
	data.savePath = savePath;
	data.filename = fileName;
	data.renderer.setProperties(data.rendererProperties);

	// rendering
	Image image = data.renderer.render();
	image.save(data.savePath + "\\" + data.filename);
}


void ImGUICallback()
{
	// RENDER WINDOW

	ImGui::Begin("Render properties");
	static int ssaaSubdivision = 2;
	static bool shadowActivate = true;
	static const Illumination items[] = { Illumination::PHONG, Illumination::LAMBERT };
	Illumination current_item = items[0];



	ImGui::PushItemWidth(150.0f);

	const char* name = "Phong";

	switch (current_item)
	{
	case Illumination::PHONG:  name = "Phong"; break;
	case Illumination::LAMBERT: name = "Lambert"; break;
	default:
		name = "Phong";
		break;
	}

	if (ImGui::BeginCombo("##select material", name)) // The second parameter is the label previewed before opening the combo.
	{
		int size = IM_ARRAYSIZE(items);
		for (int n = 0; n < size; n++)
		{
			bool is_selected = (current_item == items[n]);
			switch (items[n])
			{
			case Illumination::PHONG:  name = "Phong"; break;
			case Illumination::LAMBERT: name = "Lambert"; break;
			default:
				name = "Phong";	break;
			}
			if (ImGui::Selectable(name, is_selected)) {
				current_item = items[n];
				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}
		}

		ImGui::EndCombo();
	}


	//ImGui::Checkbox("Shadows", &shadowActivate);
	ImGui::SliderInt("SSAA subdivisions", &ssaaSubdivision, 0, 16);

	static char filename[128] = "renderedImage.jpg";
	static char filepath[128] = "E:\\dev\\Raytracing";
	static float img_width = 800.f;
	static float img_height = 800.f;


	ImGui::InputTextWithHint("Enter image name", "filename and extension", filename, IM_ARRAYSIZE(filename));
	ImGui::InputFloat("Width", &img_width);
	ImGui::InputFloat("height", &img_height);
	ImGui::InputTextWithHint("Enter save path", "path", filepath, IM_ARRAYSIZE(filepath));

	if (ImGui::Button("-- RENDER --")) renderCallback(img_width, img_height, ssaaSubdivision, shadowActivate, Illumination::LAMBERT, filepath, filename);

	static char sceneName[128] = "scene1.json";
	static char scenePath[128] = "D:\\Dev\\GPUdev\\ESGI\\Raytracing\\outputs";

	ImGui::InputTextWithHint("Enter scene name", "scene name", sceneName, IM_ARRAYSIZE(sceneName));
	ImGui::InputTextWithHint("Enter scene path", "scene path", scenePath, IM_ARRAYSIZE(scenePath));

	if (ImGui::Button("-- LOAD SCENE --"))
	{
		//loadSceneCallBack(sceneName, scenePath);
	}
	if (ImGui::Button("-- SAVE SCENE --"))
	{
		//saveceneCallBack(sceneName, scenePath);
	}
	ImGui::End();
}

int main()
{
	std::string title = "RayZ - a very very very very simple raytracer";
	Window w(800, 800, title);
	w.setBackgroundColor(0.99, 0.90, 0.94);
	while (w.isOpen()) w.run(ImGUICallback);
	w.terminate();
	return 0;

}
