#include "Engine.h"
#include <fstream>
#include <string>
#include "Shader.h"
#include "Texture2D.h"

bool Engine::Initialize(int width, int height, const char* windowName)
{
	this->width = width;
	this->height = height;

	glfwInit();
	// Configure OpenGL Version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Core-profile means we'll get access to a smaller subset of OpenGL features
	// without backwards-compatible features we no longer need
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// Create window
	window = glfwCreateWindow(width, height, windowName, NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);

	// Calbacks: We register the callback functions after we've created the window
	// and before the render loop is initiated.

	//Register resize function callback
	glfwSetFramebufferSizeCallback(window, Framebuffer_size_callback);

	// Initialize GLAD: load all OpenGL function pointers
	// We pass GLAD the function to load the address of the OpenGL function pointers which is OS - specific
	// GLFW gives us glfwGetProcAddress that defines the correct function based on which OS we're compiling for.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	return true;
}

void Engine::Run()
{
	// Simple render loop. It stops when we close the window
	while (!glfwWindowShouldClose(window))
	{
		// Input
		ProcessInput(window);

		// Buffer clearing
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Rendering

		// Check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents(); //input events (Mouse, keyboard, window resize...)
	}
}

void Engine::Stop()
{
	// Clean glfw resources
	glfwTerminate();
}

// Callback called whenever we resize the window
void Engine::Framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// Process all input: query GLFW whether relevant keys are pressed/released this frame and react
void Engine::ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}