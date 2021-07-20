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

void render_to_jpg_func(int W, int H, const char* directory, const char* filename)
{
	Scene scene(
		{
			new Sphere({ 0, 0, -5 }, { 0, 0, 0 }, 1),
			new Sphere({ 1.75, 2, -17 }, { 0, 0, 0 }, 1)
		},
		{
			new Light({ 50, 5, 0 }, {}, { 1, 1, 1 }, { 0.6, 0.6, 0.6 })
		},
		{ 0.3, 0.3, 0.3 },
		{ 0.2, 0.2, 0.2 }
	);
	Camera camera(10);
	Renderer renderer(W, H);
	Image image = renderer.render(scene, camera);
	std::string path = directory;
	path.append("\\");
	path.append(filename);
	image.save(path);
}


void render_callback() {

	// RENDER WINDOW
	{
		ImGui::Begin("Render");
		static char name[128] = "default.jpg";
		static char path[128] = "D:\\Dev\\GPUdev\\ESGI\\Raytracing\\outputs";
		static float img_width = 800.f;
		static float img_height = 800.f;

		ImGui::InputTextWithHint("Enter image name", "filename and extension", name, IM_ARRAYSIZE(name));
		ImGui::InputFloat("Width", &img_width);
		ImGui::InputFloat("height", &img_height);
		ImGui::InputTextWithHint("Enter save path", "path", path, IM_ARRAYSIZE(path));

		if (ImGui::Button("-- RENDER --")) render_to_jpg_func(img_width, img_height, path, name);
		ImGui::End();

	}


	// PROPERTY WINDOW
	{

		ImGui::Begin("Propetry");

		static float pos[3] = { .0f,.0f,.0f };
		static float rot[3] = { .0f,.0f,.0f };
		static float scale[3] = { .0f,.0f,.0f };
		static const char* items[] = { "Phong", "Lambert", "Unlit" };
		static float col[4] = { 0.5,0.15,0.28 };
		static float width, height;


		if (ImGui::CollapsingHeader("Transform"))
		{


			ImGui::PushItemWidth(50.0f);

			ImGui::Text("Position");


			ImGui::DragFloat("##PositionX", &pos[0], 0.1f, 0.0f, 0.0f, "%.2f");
			ImGui::SameLine(); ImGui::DragFloat("##PositionY", &pos[1], 0.1f, 0.0f, 0.0f, "%.2f");
			ImGui::SameLine(); ImGui::DragFloat("##PositionZ", &pos[2], 0.1f, 0.0f, 0.0f, "%.2f");

			ImGui::Text("Rotation"); // TODO : glm::rotate

			ImGui::DragFloat("##RotationX", &rot[0], 0.1f, 0.0f, 0.0f, "%.2f");
			ImGui::SameLine(); ImGui::DragFloat("##RotationY", &rot[1], 0.1f, 0.0f, 0.0f, "%.2f");
			ImGui::SameLine(); ImGui::DragFloat("##RotationZ", &rot[2], 0.1f, 0.0f, 0.0f, "%.2f");


			ImGui::Text("Scale");

			ImGui::DragFloat("##ScaleX", &scale[0], 0.1f, 0.0f, 0.0f, "%.2f");
			ImGui::SameLine(); ImGui::DragFloat("##ScaleY", &scale[1], 0.1f, 0.0f, 0.0f, "%.2f");
			ImGui::SameLine(); ImGui::DragFloat("##ScaleZ", &scale[2], 0.1f, 0.0f, 0.0f, "%.2f");


		}

		if (ImGui::CollapsingHeader("Material"))
		{
			static const char* current_item = items[0];

			ImGui::PushItemWidth(150.0f);


			if (ImGui::BeginCombo("##select material", current_item)) // The second parameter is the label previewed before opening the combo.
			{
				for (int n = 0; n < IM_ARRAYSIZE(items); n++)
				{
					bool is_selected = (current_item == items[n]); // You can store your selection however you want, outside or inside your objects
					if (ImGui::Selectable(items[n], is_selected)) {
						current_item = items[n];
						if (is_selected)
							ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)7

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
	}




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
