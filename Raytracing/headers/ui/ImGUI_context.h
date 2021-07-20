#pragma once
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "IRenderContext.h"
#include "window.h"
#include  <mutex>


class ImGUI_Context :IRenderContext {
private:
	static ImGUI_Context* instance;
	Window* _window;
	static std::mutex _mutex;

public:
	ImGUI_Context(Window* window) : _window(window) { };
	~ImGUI_Context() {};
	ImGUI_Context(ImGUI_Context& other) = delete; // not cloneable
	void operator=(const ImGUI_Context&) = delete; // not assigneable
	static ImGUI_Context* getInstance(Window* window);

	bool isOpen();

	void init() override;
	void preRender() override;
	void render() override;
	void postRender() override;
	void terminate() override;

};
