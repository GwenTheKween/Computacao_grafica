#include "dm.h"

float vertices[]={
	-200,-150,
	200, -150,
	200,150,
	-200,150
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

		teste.set(vertices, indices, 4, 2, 6, GL_TRIANGLES);

		dm.register_VAO(teste);

		dm.run();
	}catch (std::exception& e){
		std::cerr << e.what() <<std::endl;
	}
	return 0;
}
