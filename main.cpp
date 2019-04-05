#include "botoes.h"

#define WIDTH 800
#define HEIGHT 600

DisplayManager dm;
std::vector<botao> b;

void backBlue(){
	dm.clearWindow(0.0f,0.0f,1.0f);
}

void backGreen(){
	dm.clearWindow(0.0f,1.0f,0.0f);
}

void nada(){
	return;
}

void mouseButton(GLFWwindow* w, int button, int action, int mods){
	if(GLFW_MOUSE_BUTTON_LEFT == button && action == GLFW_PRESS){
		double x,y;
		glfwGetCursorPos(w, &x, &y);
		for(int i=0;i<b.size();i++){
			if(b[i].inside(x,y)){
				b[i].press();
				break;
			}
		}
	}
}

botao criaBotaoLimparTela(){
	//lata de lixo
	float vertices[16];
	unsigned int indices[] = {0,1,2,2,3,0, 4,5,6,6,7,4};

	//corpo da lata de lixo
	vertices[0]  =  50;
	vertices[1]  = 475;
	vertices[2]  =  75;
	vertices[3]  = 575;
	vertices[4]  = 125;
	vertices[5]  = 575;
	vertices[6]  = 150;
	vertices[7]  = 475;

	//tampa da lata de lixo
	vertices[8]  =  50;
	vertices[9]  = 470;
	vertices[10] =  75;
	vertices[11] = 450;
	vertices[12] = 125;
	vertices[13] = 450;
	vertices[14] = 150;
	vertices[15] = 470;

	botao b(vertices,indices, 8, 12, backBlue);

	/*
	//seta de rewind
	float vertices[12];
	unsigned int indices[6]={0,1,2,3,4,5};

	//primeiro triangulo
	vertices[0] =  50;
	vertices[1] = 525;

	vertices[2] = 125;
	vertices[3] = 575;

	vertices[4] = 125;
	vertices[5] = 475;

	//segundo  triangulo
	vertices[6] = 85;
	vertices[7] = 525;

	vertices[8] = 160;
	vertices[9] = 575;

	vertices[10] = 160;
	vertices[11] = 475;

	botao b(vertices,indices, 6,6,backBlue);
	*/
	return b;
}

botao criaBotaoTerminar(){
	float vertices[6];
	unsigned int indices[3] = {0,1,2};

	vertices[0] = 750;
	vertices[1] = 525;

	vertices[2] = 665;
	vertices[3] = 575;

	vertices[4] = 665;
	vertices[5] = 475;

	botao b(vertices,indices, 3, 3, backGreen);

	return b;
}

int main(){
	float vertices[8];
	unsigned int indices[] = {0, 1, 2, 2, 3, 0};
	try{
		dm.init(WIDTH,HEIGHT);

		b.push_back(criaBotaoLimparTela());
		b.push_back(criaBotaoTerminar());

		for(int i=0;i<b.size();i++)
			dm.register_VAO(b[i].getID());

		dm.registerMouseButtonCallback(mouseButton);

		dm.clearWindow(1.0f,1.0f,1.0f);

		dm.run();
	}catch (std::exception& e){
		std::cerr << e.what() <<std::endl;
	}
	return 0;
}
