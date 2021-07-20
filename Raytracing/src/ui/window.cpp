#include "../../headers/ui/window.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "../../headers/ui/OpenGL_context.h"
#include "../../headers/ui/ImGUI_context.h"

Window::Window(int _width, int _height, std::string& _title, GLFWmonitor* _monitor, GLFWwindow* _share) :
	width(_width), height(_height), title(_title), monitor(_monitor), share(_share), window(NULL)
{

	OpenGL_Context::getInstance(this);
	OpenGL_Context::getInstance(this)->init();
	ImGUI_Context::getInstance(this);
	ImGUI_Context::getInstance(this)->init();

}

void Window::run(void(*render_callback)())
{
	OpenGL_Context::getInstance(this)->preRender();
	ImGUI_Context::getInstance(this)->preRender();


	OpenGL_Context::getInstance(this)->render(); // /!\ call poll event => must be call befor imgui widget render to enable input event;
	ImGUI_Context::getInstance(this)->render();
	render_callback();

	ImGUI_Context::getInstance(this)->postRender();
	OpenGL_Context::getInstance(this)->postRender();
}

bool Window::isOpen()
{
	return OpenGL_Context::getInstance(this)->isOpen();
}

void  Window::terminate() {
	ImGUI_Context::getInstance(this)->terminate();
	OpenGL_Context::getInstance(this)->terminate();
}