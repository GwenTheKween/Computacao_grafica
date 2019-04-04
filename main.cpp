#include "botoes.h"

#define WIDTH 800
#define HEIGHT 600

DisplayManager dm;
std::vector<botao> b;

void nada(){
	printf("foi\n");
	return;
}

void mouseButton(GLFWwindow* w, int button, int action, int mods){
	if(GLFW_MOUSE_BUTTON_LEFT == button && action == GLFW_PRESS){
		double x,y;
		glfwGetCursorPos(w, &x, &y);
		printf("%lf\t%lf\n",x,y);
		for(int i=0;i<b.size();i++){
			if(b[i].inside(x,y)){
				b[i].press();
				break;
			}
		}
	}
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
	try{
		dm.init(WIDTH,HEIGHT);

		b.push_back(cria_botao_sair());
		b.push_back(cria_botao_2());

		dm.register_VAO(b[0].getID());
		dm.register_VAO(b[1].getID());

		dm.registerMouseButtonCallback(mouseButton);

		dm.run();
	}catch (std::exception& e){
		std::cerr << e.what() <<std::endl;
	}
	return 0;
}
