#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <iostream>

const char* vertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

// Functions declaration
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main()
{
	glfwInit();
	// Configure window
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Core-profile means we'll get access to a smaller subset of OpenGL features
	// without backwards-compatible features we no longer need
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	const int window_width = 1280;
	const int window_height = 1000;

	// Create window
	GLFWwindow* window = glfwCreateWindow(window_width, window_height, "Second Floor", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Calbacks: We register the callback functions after we've created the window
	// and before the render loop is initiated.

	//Register resize function callback
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Initialize GLAD: load all OpenGL function pointers
	// We pass GLAD the function to load the address of the OpenGL function pointers which is OS - specific
	// GLFW gives us glfwGetProcAddress that defines the correct function based on which OS we're compiling for.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Triangle
	float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};	

	// vertex shader creation
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// Next we attach the shader source code to the shader object and compile the shader:
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// Check if shader compilation was successful
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		return 0;
	}

	// Fragment shader (orange color)
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// Check if shader compilation was successful
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		return 0;
	}

	// To use the shaders we have to link them to a shader program object
	unsigned int shaderProgram = glCreateProgram();

	// Attach shaders and then link them
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// Check program compilation
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) 
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
		return 0;
	}

	// Once the program is compiled we can delete the shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Link vertex attributes (indicate OpenGL how to read the triangle)
	glVertexAttribPointer(0, //(Position shader info, location = 0)
		3, //size of vertex attribute (vec3)
		GL_FLOAT, //type of data
		GL_FALSE, //Normalize data() //-1,+1
		3 * sizeof(float), //Size of data stride (3 floats)
		(void*)0); //Starting point of data info [0]

	glEnableVertexAttribArray(0);

	// Use of shader
	// 
	// Create a VAO (As soon as we want to draw an object, 
	// we simply bind the VAO with the preferred settings (VBO)
	// before drawing the object and that is it
	unsigned int VAO = 0;
	glGenVertexArrays(1, &VAO);

	unsigned int VBO = 0;
	glGenBuffers(1, &VBO);

	// 1. bind Vertex Array Object
	glBindVertexArray(VAO);
	// 2. copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //Array buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //Copy data to the buffer
	//The position data of the triangle does not change and stays the same for every render call so its usage type should best be GL_STATIC_DRAW
	// 3. then set our vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Simple render loop. It stops when we close the window
	while (!glfwWindowShouldClose(window))
	{
		// Input
		processInput(window);

		// Rendering
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Triangle rendering
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3); // Primitive type, starting index, last index

		// Check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents(); //input events (Mouse, keyboard, window resize...)
	}
	
	// De-allocate resources
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

	// Clean glfw resources
	glfwTerminate();

	return 0;
}

// Functions implementation
// 
// Callback called whenever we resize the window
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// Process all input: query GLFW whether relevant keys are pressed/released this frame and react
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}