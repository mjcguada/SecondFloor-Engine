#pragma once
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <iostream>

class Engine
{
public:
	bool Initialize(int width, int height, const char* windowName);
	void Run();
	void Stop();

private:
	// Window attributes
	GLFWwindow* window = nullptr;
	int width = 0;
	int height = 0;

	// Functions declaration
	static void Framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void ProcessInput(GLFWwindow* window);
};