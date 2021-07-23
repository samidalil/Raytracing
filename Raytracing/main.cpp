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
#include "headers/primitives/Plane.h"
#include "headers/primitives/Cube.h"
#include "headers/lights/AmbientLight.h"
#include "headers/primitives/Square.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "headers/ui/window.h"

struct DataContext {
	RendererProperties rendererProperties;
	Renderer renderer;
	std::string savePath = "E:\\dev\\Raytracing\\result.jpg";
};

int main()
{
	auto material1 = std::make_shared<Material>(Color::white, Color::white, Color::white * 0.2, 1);
	auto material2 = std::make_shared<Material>(Color::white, Color::white, Color::white * 0.2, 1);
	material2->texture = std::make_shared<Image>("E:\\dev\\Raytracing\\texture2.jpg");;
	auto pos = Vector(-2, 2.4, -35);
	auto pos2 = Vector(5, 0, -10);
	auto s1 = std::make_shared<Cube>(pos, Vector(0.2, 0.7, 0), 1.7, material2);
	auto s2 = std::make_shared<Sphere>(pos + (pos2 - pos) / 2, Vector(), 1, material1);
	auto sq1 = std::make_shared<Square>(Vector(0, -2, -25), Vector(), 0.5, material2);
	auto l1 = std::make_shared<AmbientLight>(pos2, Vector(0, 0, 0), Color::white * 0.5, Color::white * 0.3);
	auto l2 = std::make_shared<AmbientLight>(Vector(-15, 0, 0), Vector(0, 0, 0), Color::white * 0.15, Color::white * 0.2);
	auto scene = std::make_shared<Scene>(Color::blue * 0.1 + Color::red * 0.15, Color::white * 0.4);
	auto camera = std::make_shared<Camera>(10);

	scene->add(s1);
	scene->add(s2);
	scene->add(sq1);
	scene->add(l1);
	scene->add(l2);

	DataContext data;

	data.rendererProperties.scene = scene;
	data.rendererProperties.camera = camera;
	data.rendererProperties.ssaaSubdivisions = 2;
	data.rendererProperties.width = 800;
	data.rendererProperties.height = 800;
	data.renderer.setProperties(data.rendererProperties);
	
	Image image = data.renderer.render();
	image.save(data.savePath);
}

/*void render_to_jpg_func(int W, int H, Illumination illuminationModel, const char* directory, const char* filename)
{
	Material blue({ 0, 0, 0.8f }, { 0, 0, 0.5f }, { 1, 1, 1 }, 0.5f);
	Material red({ 0.8f, 0, 0 }, { 0.5f, 0, 0 }, { 1, 1, 1 }, 0.5f);
	Material green({ 0, 0.8f, 0 }, { 0, 1.f, 0 }, { 1,1 , 1 }, 1.f);
	Material m({ 0, 0, 0.8f }, { 0, 0, 0.5f }, { 1, 1, 1 }, 0.2f);

	Scene scene(
		{
			new Sphere({ 0, -2, -20 }, { 0, 0, 0 }, 1, blue),
			new Sphere({ 0, 1, -25 }, { 0, 0, 0 }, 1, red),
			new Cube({ 2, 0, -40 }, { 0, 2, 0.5f }, 1, green),
			new Plane({ 0, 0, -50 }, { 0, 0, 0 }, 1, m)
		},
		{
			new Light({ 0, -10, -20}, {0,1,0.5f}, { 1, 1, 1 }, { 0.6, 0.6, 0.6 })
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
}


int main()
{
	std::string title = "RayZ";
	Window w(1920, 1080, title);
	w.setBackgroundColor(0.99, 0.90, 0.94);
	while (w.isOpen()) w.run(render_callback);
	w.terminate();
	return 0;
}
*/
