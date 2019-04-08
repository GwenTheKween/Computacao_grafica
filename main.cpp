#include "botoes.h"

#define WIDTH 800
#define HEIGHT 600

//declaracao de variaveis globais
//gerenciador da parte grafica:
DisplayManager dm;
//gerenciador da interface grafica
std::vector<botao> b;
//coordenadas do poligono entrado pelo usuario
std::vector<float> input_coordinates;
//informacao do poligono a ser desenhado
VAO_INFO poly;
//informacao do poligono que o ususario esta entrando
VAO_INFO input_draw;
//cor usada para desenhar o poligono
float color[3];
//se o programa esta aceitando input para vertices do poligono
bool acceptInput;

void finishPolygon(){

	std::vector<float> polygon;
	float color[]={1.0f,1.0f,1.0f};
	//CHAMADA DE FUNCAO DO LUIS
	//poligon = PoliFill(input_coordinates);

	dm.deregister_VAO(input_draw);
	//exemplo para teste:
	polygon = input_coordinates;

	poly.start(input_coordinates,2,GL_LINE_LOOP,GL_STATIC_DRAW,color);

	dm.register_VAO(poly);

	//dm.setClearColor(0.8f,0.0f,0.0f);
	acceptInput = false;

	//o indice do botao que termina o poligono eh 1
	b[1].disable();
	dm.update_VAO(b[1].getID());
}

void clearScreen(){
	input_coordinates.clear();

	dm.deregister_VAO(poly);
	dm.deregister_VAO(input_draw);

	//dm.setClearColor(0.0f,0.8f,0.0f);
	acceptInput = true;

	//o indice do botao que termina o poligono eh 1
	b[1].enable();
	dm.update_VAO(b[1].getID());
}

void mouseButton(GLFWwindow* w, int button, int action, int mods){
	if(GLFW_MOUSE_BUTTON_LEFT == button && action == GLFW_PRESS){
		double x,y;
		int i;
		glfwGetCursorPos(w, &x, &y);
		for(i=0;i<b.size();i++){
			if(b[i].inside(x,y)){
				b[i].press();
				break;
			}
		}
		if(i == b.size() && acceptInput){
			input_coordinates.push_back((float)x);
			input_coordinates.push_back((float)y);
			if(input_coordinates.size() == 2){ 
				//se tem mais que uma coordenada, aloca um buffer para desenhar o poligono
				input_draw.start(input_coordinates, 2, GL_LINE_LOOP, GL_DYNAMIC_DRAW,color);
				dm.register_VAO(input_draw);
			}else if(input_coordinates.size() > 4){
				input_draw.updateVertex(input_coordinates, 2, GL_DYNAMIC_DRAW);
				//se tem mais que 2 coordenadas, o poligono estava sendo desenhado e eh necessario fazer update do buffer anterior
				dm.update_VAO(input_draw);
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

	botao b(vertices,indices, 8, 12, clearScreen);

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

	botao b(vertices,indices, 3, 3, finishPolygon);

	return b;
}

int main(){
	color[0] = 1.0f;
	color[1] = 1.0f;
	color[2] = 1.0f;
	acceptInput = true;
	try{
		dm.init(WIDTH,HEIGHT);

		b.push_back(criaBotaoLimparTela());
		b.push_back(criaBotaoTerminar());
//		printf("%d\n",b[1].getID().VAO_ID);

		for(int i=0;i<b.size();i++)
			dm.register_VAO(b[i].getID());

		dm.registerMouseButtonCallback(mouseButton);

		dm.run();
	}catch (std::exception& e){
		std::cerr << e.what() <<std::endl;
	}
	poly.finish();
	return 0;
}
