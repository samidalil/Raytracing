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

#include "headers/image/Image.h"
#include "headers/primitives/Sphere.h"
#include "headers/engine/Camera.h"
#include "headers/engine/Scene.h"
#include "headers/engine/Renderer.h"
#include "headers/texture/Material.h"
#include "headers/lights/AmbientLight.h"
#include "headers/lights/PointLight.h"
#include "headers/primitives/Plane.h"
#include "headers/primitives/Cube.h"
#include "headers/primitives/Square.h"
#include "headers/primitives/Cylinder.h"
#include "headers/primitives/Triangle.h"
#include "headers/primitives/Cone.h"
#include "headers/engine/Serializer.h"
#include "headers/ui/window.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

struct DataContext {
	RendererProperties rendererProperties;
	Renderer renderer;
	std::string savePath;
};

DataContext data;

void renderCallback(DataContext data)
{	
	data.rendererProperties.camera = std::make_shared<Camera>(10);
	data.renderer.setProperties(data.rendererProperties);

	data.renderer.render().save(data.savePath);
	std::cout << "finished rendering" << std::endl;
}

void loadSceneCallBack(const std::string& path, const std::string& name) {
	Serializer serializer;

	data.rendererProperties.scene = serializer.deserializeScene(path + "\\" + name);
}

void saveSceneCallBack(const std::string& path, const std::string& name) {
	Serializer serializer(path + "\\" + name, "");

	serializer.serializeScene(data.rendererProperties.scene);
}

void ImGUICallback()
{
	// RENDER WINDOW

	ImGui::Begin("Render properties");

	static const Illumination items[] = { Illumination::PHONG, Illumination::LAMBERT };
	static char filename[128] = "renderedImage.jpg";
	static char filepath[128] = "D:\\Raytracing";
	static char sceneName[128] = "scene1.json";
	static char scenePath[128] = "D:\\Dev\\GPUdev\\ESGI\\Raytracing\\outputs";

	ImGui::PushItemWidth(150.0f);

	char* name = "Phong";

	switch (data.rendererProperties.illumination)
	{
	case Illumination::LAMBERT:  name = "Lambert"; break;
	default: name = "Phong";  break;
	}

	if (ImGui::BeginCombo("##select material", name))
	{
		int size = IM_ARRAYSIZE(items);

		for (int n = 0; n < size; n++)
		{
			bool isSelected = data.rendererProperties.illumination == items[n];

			switch (items[n])
			{
			case Illumination::LAMBERT: name = "Lambert"; break;
			default: name = "Phong"; break;
			}

			if (ImGui::Selectable(name, isSelected)) {
				data.rendererProperties.illumination = items[n];
				if (isSelected) ImGui::SetItemDefaultFocus();
			}
		}

		ImGui::EndCombo();
	}


	ImGui::Checkbox("Enable shadows", &data.rendererProperties.enableShadows);
	ImGui::SliderInt("SSAA subdivisions", &data.rendererProperties.ssaaSubdivisions, 1, 16);
	ImGui::SliderInt("DOF samples", &data.rendererProperties.dofSamples, 1, 500);

	ImGui::End();

	ImGui::Begin("Image");

	ImGui::InputInt("Width", &data.rendererProperties.width);
	ImGui::InputInt("height", &data.rendererProperties.height);
	ImGui::InputTextWithHint("Enter save path", "Path without \\ at the end", filepath, IM_ARRAYSIZE(filepath));
	ImGui::InputTextWithHint("Enter image name", "Filename and extension", filename, IM_ARRAYSIZE(filename));
	data.savePath = std::string(filepath) + "\\" + std::string(filename);
	
	ImGui::InputTextWithHint("Enter scene name", "scene name", sceneName, IM_ARRAYSIZE(sceneName));
	ImGui::InputTextWithHint("Enter scene path", "scene path", scenePath, IM_ARRAYSIZE(scenePath));

	if (ImGui::Button("-- LOAD SCENE --")) loadSceneCallBack(sceneName, scenePath);
	if (ImGui::Button("-- SAVE SCENE --")) saveSceneCallBack(sceneName, scenePath);

	if (ImGui::Button("-- RENDER --")) renderCallback(data);
	
	ImGui::End();
}

int main()
{
	std::string title = "RayZ - a very very very very simple raytracer";
	Window w(1920, 1080, title);
	w.setBackgroundColor(0.99, 0.90, 0.94);
	while (w.isOpen()) w.run(ImGUICallback);
	w.terminate();
	return 0;
}
