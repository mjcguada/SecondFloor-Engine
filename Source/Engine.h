#pragma once
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

class Engine
{
public:
	Engine(int width, int height, const char* windowName);
	~Engine();

	bool Initialize();
	void Run();

private:
	// Window attributes
	GLFWwindow* window = nullptr;
	int width = 0;
	int height = 0;
	const char* windowName = nullptr;

	// Functions declaration
	static void Framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void ProcessInput(GLFWwindow* window);
};