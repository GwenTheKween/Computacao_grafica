#include "botoes.h"

#define WIDTH 800
#define HEIGHT 600

DisplayManager dm;

void nada(){
	return;
}

botao cria_botao_sair(){
	float vertices[8];
	vertices[0] = -750;
	vertices[2] = -500;
	vertices[4] = -500;
	vertices[6] = -750;

	vertices[1] = -550;
	vertices[3] = -550;
	vertices[5] = -450;
	vertices[7] = -450;

	botao b(vertices,nada);
	return b;
}

botao cria_botao_2(){
	float vertices[8];
	vertices[0] = 750;
	vertices[2] = 500;
	vertices[4] = 500;
	vertices[6] = 750;

	vertices[1] = -550;
	vertices[3] = -550;
	vertices[5] = -450;
	vertices[7] = -450;

	botao b(vertices,nada);
	return b;
}

int main(){
	float vertices[8];
	unsigned int indices[] = {0, 1, 2, 2, 3, 0};
	botao b[2];
	try{
		dm.init(WIDTH,HEIGHT);

		b[0] = cria_botao_sair();
		b[1] = cria_botao_2();

		dm.register_VAO(b[0].getID());
		dm.register_VAO(b[1].getID());

		dm.run();
	}catch (std::exception& e){
		std::cerr << e.what() <<std::endl;
	}
	return 0;
}
