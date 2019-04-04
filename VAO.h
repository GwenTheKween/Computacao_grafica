#ifndef VAO_CLASS
#define VAO_CLASS

#include <iostream>
#include "include/glad/glad.h"
#include <GLFW/glfw3.h>

struct VAO_INFO{
	unsigned int VAO_ID;
	unsigned int VBO_ID;
	unsigned int EBO_ID;
	unsigned int drawStyle;
	unsigned int indexCount;

	void set(float* vertices, 
			 unsigned int* indices, 
			 unsigned int vertexCount, 
			 unsigned int indexCount, 
			 unsigned int draw)
	{
		glGenVertexArrays(1, &VAO_ID);
		glGenBuffers(1, &VBO_ID);
		glGenBuffers(1, &EBO_ID);

		glBindVertexArray(VAO_ID);

		glBindBuffer(GL_ARRAY_BUFFER, VBO_ID);
		glBufferData(GL_ARRAY_BUFFER,vertexCount * sizeof(vertices[0]), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(indices[0]), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindVertexArray(0);

		drawStyle = draw;
		this -> indexCount = indexCount;
	}

	void unset(){
		glDeleteVertexArrays(1,&VAO_ID);
		glDeleteBuffers(1,&VBO_ID);
		glDeleteBuffers(1,&EBO_ID);
	}
};

#endif
