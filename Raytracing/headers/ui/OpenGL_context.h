#pragma once
#include "IRenderContext.h"
#include "window.h"
#include  <mutex>


class OpenGL_Context :IRenderContext {
private:
	static OpenGL_Context* instance;
	Window* _window;
	static std::mutex _mutex;

public:
	OpenGL_Context(Window* window) { _window = window; };
	~OpenGL_Context() {};
	OpenGL_Context(OpenGL_Context& other) = delete; // not cloneable
	void operator=(const OpenGL_Context&) = delete; // not assigneable
	static OpenGL_Context* getInstance(Window* window);

	inline bool isOpen() { return !glfwWindowShouldClose(_window->window); };

	void init() override;
	void preRender() override;
	void render() override;
	void postRender() override;
	void terminate() override;

};
