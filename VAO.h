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

	void start(float* vertices, 
			 unsigned int* indices, 
			 unsigned int vertexCount, 
			 unsigned int vertexDimension, //se for 2D, multiplica a contagem de vertices por 2, se for 3D, multiplica por 3
			 unsigned int indexCount, 
			 unsigned int draw)
	{
		glGenVertexArrays(1, &VAO_ID);
		glGenBuffers(1, &VBO_ID);
		glGenBuffers(1, &EBO_ID);

		if(vertexCount > 0){
			glBindVertexArray(VAO_ID);

			glBindBuffer(GL_ARRAY_BUFFER, VBO_ID);
			glBufferData(GL_ARRAY_BUFFER,vertexCount * vertexDimension * sizeof(vertices[0]), vertices, GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_ID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(indices[0]), indices, GL_STATIC_DRAW);

			glVertexAttribPointer(0, vertexDimension, GL_FLOAT, GL_FALSE, vertexDimension*sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);

			glBindVertexArray(0);
		}

		drawStyle = draw;
		this -> indexCount = indexCount;
		uses_index = true;
	}

	void start(std::vector<float> vertices,
			 unsigned int vertexDimension,
			 unsigned int draw,
			 unsigned int memory_type = GL_STATIC_DRAW)
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
	}

	void finish(){
		glDeleteVertexArrays(1,&VAO_ID);
		glDeleteBuffers(1,&VBO_ID);
		if(EBO_ID) glDeleteBuffers(1,&EBO_ID);
	}

	void updatePoints(
			std::vector<float> vertices, 
			unsigned int vertexDimension, 
			unsigned int memory_type){

		glBindVertexArray(VAO_ID);
		glBindBuffer(GL_ARRAY_BUFFER, VBO_ID);

		glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(vertices[0]), vertices.data(), memory_type);
		glVertexAttribPointer(0, vertexDimension, GL_FLOAT, GL_FALSE, vertexDimension*sizeof(float), (void*) 0);
		glEnableVertexAttribArray(0);

		glBindVertexArray(0);

		indexCount = vertices.size()/vertexDimension;
	}
};

#endif
