#include "dm.h"

float vertices[]={
	-0.5f, -0.5f,0.0f,
	0.5f, -0.5f, 0.0f,
	0.5f, 0.5f, 0.0f,
	-0.5f, 0.5f, 0.0f
};

unsigned int indices[] = {
	0, 1, 2, 
	2, 3, 0
};


int main(){
	DisplayManager dm;
	try{
		dm.init(800,600);

		VAO_INFO teste;

		teste.set(vertices, indices, 12, 6, GL_LINE_LOOP);

		dm.register_VAO(teste);

		dm.run();
	}catch (std::exception& e){
		std::cerr << e.what() <<std::endl;
	}
	return 0;
}
