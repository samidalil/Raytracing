#include "../../headers/ui/OpenGL_context.h"
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

OpenGL_Context* OpenGL_Context::instance = nullptr;
std::mutex OpenGL_Context::_mutex;


OpenGL_Context* OpenGL_Context::getInstance(Window* window) {
	std::lock_guard<std::mutex> lock(_mutex);
	if (instance == nullptr)
	{
		instance = new OpenGL_Context(window);
	}
	return instance;
};


void OpenGL_Context::init()
{
	// 1. Init GLFW
	{
		if (!glfwInit())
		{
			std::cerr <<"--- GLFW : Failed to init GLFW" << std::endl;
			exit(EXIT_FAILURE);
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		std::clog << "--- GLFW : Initialize with OpenGL" << GLFW_CONTEXT_VERSION_MAJOR << "." << GLFW_CONTEXT_VERSION_MINOR << std::endl;
	}

	// 2. Attach openGL context to GLFW window
	{
		_window->window = glfwCreateWindow(_window->width, _window->height, _window->title.c_str(), _window->monitor, _window->share);
		if (!_window->window) {
			std::cerr << "--- GLFW : Window creation failed." << std::endl;
			glfwTerminate();
			exit(EXIT_FAILURE);
		}		glfwMakeContextCurrent(_window->window);
	}

	// .3 Init Glad
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cerr <<"--- GLAD : glad failed to initialize" << std::endl ;
			exit(EXIT_FAILURE);
		}
	}

	//.4 Init callbacks and set options
	{
		glViewport(0, 0, _window->width, _window->height);
		glfwSetFramebufferSizeCallback(_window->window, framebuffer_size_callback);
		glEnable(GL_DEPTH_TEST);
		glfwSetInputMode(_window->window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
	}

}

void OpenGL_Context::preRender()
{
	glfwPollEvents();

}

void OpenGL_Context::render()
{
	glfwSwapBuffers(_window->window);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGL_Context::postRender()
{
}

void OpenGL_Context::terminate()
{
	std::clog <<"--- GLFW : Terminate window" << std::endl;
	glfwTerminate();
}