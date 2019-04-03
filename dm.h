#ifndef DISPLAY_MANAGER
#define DISPLAY_MANAGER

//#define DEBUG
#define MAX_VERTICES 4

//standard libraries
#include <iostream>
#include <fstream>
#include <exception>
#include <cstring>
#include <string>

//bibliotecas graficas
#include "include/glad/glad.h"
#include <GLFW/glfw3.h>

class DisplayManager{
private:
	//members used for GLFW library
	GLFWwindow* window;
	unsigned int vertexShader;
	unsigned int fragmentShader;
	unsigned int shaderProgram;

	unsigned int VBO;//verter buffer object
	unsigned int VAO;//vertex array object
	unsigned int EBO;//Element buffer object


	//General Purpose Members
	uint32_t width, height;

public:
	DisplayManager();
	~DisplayManager();

	void init(int = 800, int = 600, const char* = nullptr);
	void run();

};

static float vertices[]={
	-0.5f, -0.5f,0.0f,
	0.5f, -0.5f, 0.0f,
	0.5f, 0.5f, 0.0f,
	-0.5f, 0.5f, 0.0f
};

static unsigned int indices[] = {
	0, 1, 2,
	2, 3, 0
};

#endif
