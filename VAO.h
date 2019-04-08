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
	bool uses_index;
	float color[3];

	void start(float* vertices, 
			 unsigned int* indices, 
			 unsigned int vertexCount, 
			 unsigned int vertexDimension, //se for 2D, multiplica a contagem de vertices por 2, se for 3D, multiplica por 3
			 unsigned int indexCount, 
			 unsigned int draw,
			 unsigned int memory_type,
			 float c[3])
	{
		glGenVertexArrays(1, &VAO_ID);
		glGenBuffers(1, &VBO_ID);
		glGenBuffers(1, &EBO_ID);

		if(vertexCount > 0){
			glBindVertexArray(VAO_ID);

			glBindBuffer(GL_ARRAY_BUFFER, VBO_ID);
			glBufferData(GL_ARRAY_BUFFER,vertexCount * vertexDimension * sizeof(vertices[0]), vertices, memory_type);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_ID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(indices[0]), indices, memory_type);

			glVertexAttribPointer(0, vertexDimension, GL_FLOAT, GL_FALSE, vertexDimension*sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);

			glBindVertexArray(0);
		}

		drawStyle = draw;
		this -> indexCount = indexCount;
		uses_index = true;
		color[0] = c[0];
		color[1] = c[1];
		color[2] = c[2];
	}

	void start(std::vector<float> vertices,
			 unsigned int vertexDimension,
			 unsigned int draw,
			 unsigned int memory_type,
			 float c[3])
	{
		glGenVertexArrays(1, &VAO_ID);
		glGenBuffers(1, &VBO_ID);
		EBO_ID = 0;

		if(vertices.size() > 0){
			glBindVertexArray(VAO_ID);

			glBindBuffer(GL_ARRAY_BUFFER, VBO_ID);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), vertices.data(), memory_type);

			glVertexAttribPointer(0, vertexDimension, GL_FLOAT, GL_FALSE, vertexDimension*sizeof(float), (void*) 0);
			glEnableVertexAttribArray(0);

			glBindVertexArray(0);
		}

		drawStyle = draw;
		indexCount = vertices.size()/vertexDimension;
		uses_index = false;
		color[0] = c[0]; 
		color[1] = c[1];
		color[2] = c[2];
	}

	void finish(){
		glDeleteVertexArrays(1,&VAO_ID);
		glDeleteBuffers(1,&VBO_ID);
		if(EBO_ID) glDeleteBuffers(1,&EBO_ID);
	}
};

#endif
