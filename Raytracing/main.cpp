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

#include "headers/Constants.h"
#include "headers/image/Image.h"
#include "headers/primitives/Sphere.h"
#include "headers/engine/Light.h"
#include "headers/engine/Camera.h"
#include "headers/engine/Scene.h"
#include "headers/engine/Renderer.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "headers/ui/window.h"

using namespace std;

void render_to_jpg_func(int W, int H, Illumination illuminationModel, const char* directory, const char* filename)
{
	Scene scene(
		{
			new Sphere({ 0, 0, -5 }, { 0, 0, 0 }, 1, Material({ 1, 1, 1 }, { 0.2, 0.2, 0.2 }, { 0.7, 0.7, 0.7 }, 0.7, Image("D:\\Dev\\GPUdev\\ESGI\\Raytracing\\resources\\sample.jpg"))),
			new Sphere({ 1.2, 1, -17 }, { 0, 0, 0 }, 1.4, Material({ 1, 1, 1 }, { 0.2, 0.2, 0.2 }, { 0.7, 0.7, 0.7 }, 0.7, Image("D:\\Dev\\GPUdev\\ESGI\\Raytracing\\resources\\sample.jpg")))
		},
		{
			new Light({ 50, 5, 0 }, {}, { 1, 1, 1 }, { 0.6, 0.6, 0.6 })
		},
		{ 0.3, 0.3, 0.3 },
		{ 0.5, 0.2, 0.3 }
	);
	Camera camera(10);
	Renderer renderer(W, H);
	renderer.setIlluminationModel(illuminationModel);
	Image image = renderer.render(scene, camera);
	std::string path = directory;
	path.append("\\");
	path.append(filename);
	image.save(path);
}


void render_callback() {
	// PROPERTY WINDOW

	ImGui::Begin("Propetry");

	static const Illumination items[] = { Illumination::PHONG, Illumination::LAMBERT,Illumination::UNLIT };
	static float col[4] = { 0.5,0.15,0.28 };
	Illumination current_item = items[0];

	if (ImGui::CollapsingHeader("Material"))
	{

		ImGui::PushItemWidth(150.0f);

		const char* name = "Phong";
		switch (current_item)
		{
		case Illumination::PHONG:  name = "Phong"; break;
		case Illumination::LAMBERT: name = "Lambert"; break;
		case Illumination::UNLIT:name = "Unlit"; break;
		default:
			name = "Phong";
			break;
		}

		if (ImGui::BeginCombo("##select material", name)) // The second parameter is the label previewed before opening the combo.
		{
			for (int n = 0; n < IM_ARRAYSIZE(items); n++)
			{
				bool is_selected = (current_item == items[n]); 
				switch (items[n])
				{
				case Illumination::PHONG:  name = "Phong"; break;
				case Illumination::LAMBERT: name = "Lambert"; break;
				case Illumination::UNLIT:name = "Unlit"; break;
				default:
					name = "Phong";
					break;
				}
					if (ImGui::Selectable(name, is_selected)) {
						current_item = items[n];
							if (is_selected)
								ImGui::SetItemDefaultFocus();   

					}

			}
			ImGui::EndCombo();
		}



		ImGui::ColorEdit4("Diffuse color", col); // TODO : link to object material
		float v;
		ImGui::SliderFloat("Roughness", &v, 0.0f, 1.0f); // TODO : link to object material
		ImGui::SliderFloat("Metallic", &v, 0.0f, 1.0f); // TODO : link to object material
		ImGui::Text("Here image picker for texture");

	}

	ImGui::End();

	// RENDER WINDOW

	ImGui::Begin("Render");
	static char name[128] = "default.jpg";
	static char path[128] = "D:\\Dev\\GPUdev\\ESGI\\Raytracing\\outputs";
	static float img_width = 800.f;
	static float img_height = 800.f;

	ImGui::InputTextWithHint("Enter image name", "filename and extension", name, IM_ARRAYSIZE(name));
	ImGui::InputFloat("Width", &img_width);
	ImGui::InputFloat("height", &img_height);
	ImGui::InputTextWithHint("Enter save path", "path", path, IM_ARRAYSIZE(path));

	if (ImGui::Button("-- RENDER --")) render_to_jpg_func(img_width, img_height, Illumination::LAMBERT, path, name);
	ImGui::End();









};


int main()
{


	std::string title = "RayZ";
	Window w(1920, 1080, title);
	w.setBackgroundColor(0.99, 0.90, 0.94);
	while (w.isOpen())
	{
		w.run(render_callback);
	}
	w.terminate();
	return 0;
}
