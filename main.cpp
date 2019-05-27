#include "botoes.h"
//#include "AET.h"

#define WIDTH 800
#define HEIGHT 600

//informacoes sobre botoes de cor
#define COLOR_BUTTON_SIZE 20
#define COLOR_BUTTON_SPACE 6
#define COLOR_BUTTON_BEGIN_X (WIDTH/2 - 2*COLOR_BUTTON_SIZE - 3*COLOR_BUTTON_SPACE/2)
#define COLOR_BUTTON_BEGIN_Y 470 //escolhido ao acaso


//ordem dos botoes no vector: {cores,terminar,limpar}
#define COLOR_BUTTON_COUNT 16
#define FINISH_BUTTON_INDEX (COLOR_BUTTON_COUNT)
#define CLEAR_BUTTON_INDEX (COLOR_BUTTON_COUNT + 1 )

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

//qual botao foi apertado, -1 se nenhum botao foi apertado
int currButtonPress;

//Vertice com as cores dos botoes:
float buttonColor[18][3]={
	//primeira tentativa de paleta, ficou meio estranha
	{0.1f,0.1f,0.1f},
	{0.0f,0.25f,0.25f},
	{0.0f,0.5f,0.0f},
	{0.0f,0.75f,0.25f},

	{0.25f,0.0f,0.5f},
	{0.25f,0.25f,0.75f},
	{0.25f,0.5f,0.5f},
	{0.25f,0.75f,0.75f},

	{0.5f,0.0f,0.0f},
	{0.5f,0.25f,0.25f},
	{0.5f,0.5f,0.0f},
	{0.5f,0.75f,0.25f},

	{0.75f,0.0f,0.5f},
	{0.75f,0.25f,0.75f},
	{0.75f,0.5f,0.5f},
	{0.75f,0.75f,0.75f},


	{1.0f,1.0f,1.0f},
	{1.0f,1.0f,1.0f}
};

//==============================================================================================================================================
//Funcoes usadas pelos botoes

void finishPolygon(){ //funcao do botao de termino do 
	std::vector<float> polygon;
	//CHAMADA DE FUNCAO DO LUIS
//	polygon = PoliFill(input_coordinates);

	dm.deregister_VAO(input_draw);
	//exemplo para teste:
	//polygon = input_coordinates;

	poly.start(polygon,2,GL_POINTS,GL_STATIC_DRAW,input_draw.color);

	dm.register_VAO(poly);

	//dm.setClearColor(0.8f,0.0f,0.0f);
	acceptInput = false;

	for(int i=0; i<= CLEAR_BUTTON_INDEX; i++){
		if(i != FINISH_BUTTON_INDEX){
			b[i].disable();
			dm.update_VAO(b[i].getID());
		}
	}
}

void clearScreen(){
	input_coordinates.clear();

	dm.deregister_VAO(poly);
	dm.deregister_VAO(input_draw);

	//dm.setClearColor(0.0f,0.8f,0.0f);
	acceptInput = true;

	for(int i=0; i<= CLEAR_BUTTON_INDEX; i++){
		if(i != FINISH_BUTTON_INDEX){
			b[i].enable();
			dm.update_VAO(b[i].getID());
		}
	}
}

void setColor(){
	input_draw.setColor(buttonColor[currButtonPress]);
	dm.update_VAO(input_draw);
}

//==============================================================================================================================================
//funcoes usadas como callback

void mouseButton(GLFWwindow* w, int button, int action, int mods){
	if(GLFW_MOUSE_BUTTON_LEFT == button && action == GLFW_PRESS){
		double x,y;
		int i;
		glfwGetCursorPos(w, &x, &y);
		for(i=0;i<b.size();i++){
			if(b[i].inside(x,y)){
				currButtonPress = i;
				b[i].press();
				break;
			}
		}
		if(i == b.size() && acceptInput){
			currButtonPress = -1;
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

//==============================================================================================================================================
//criacao de botoes

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

	botao b(vertices,indices, 8, 12, buttonColor[CLEAR_BUTTON_INDEX], clearScreen);

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

	botao b(vertices,indices, 3, 3, buttonColor[FINISH_BUTTON_INDEX],finishPolygon);

	return b;
}

/*
	Os botoes de cor estao alocados em uma matrix 4x4, e os numeros indicam qual a posicao do botao da seguinte maneira:

	1	2	3	4
	5	6	7	8
	9	a	b	c
	d	e	f	g
*/

botao criaBotaoCor(int numero){
	float x,y;

	x = COLOR_BUTTON_BEGIN_X + (numero % 4) * (COLOR_BUTTON_SIZE + COLOR_BUTTON_SPACE);
	y = COLOR_BUTTON_BEGIN_Y + (numero / 4) * (COLOR_BUTTON_SIZE + COLOR_BUTTON_SPACE);

	float vertices[8];
	unsigned int indices[6] = {0,1,2,2,3,0};

	vertices[0] = x;
	vertices[1] = y;

	vertices[2] = x + COLOR_BUTTON_SIZE;
	vertices[3] = y;

	vertices[4] = x + COLOR_BUTTON_SIZE;
	vertices[5] = y + COLOR_BUTTON_SIZE;

	vertices[6] = x;
	vertices[7] = y + COLOR_BUTTON_SIZE;

	botao b(vertices, indices, 4, 6, buttonColor[numero], setColor);

	return b;
}

//==============================================================================================================================================
//Funcao Main

int main(){
	color[0] = 1.0f;
	color[1] = 1.0f;
	color[2] = 1.0f;
	acceptInput = true;
	try{
		dm.init(WIDTH,HEIGHT);

		for(int i=0;i<COLOR_BUTTON_COUNT; i++){
			b.push_back(criaBotaoCor(i));
		}
		b.push_back(criaBotaoLimparTela());
		b.push_back(criaBotaoTerminar());
//		printf("%d\n",b[1].getID().VAO_ID);

//		printf("%d\n",b[1].getID().VAO_ID);

//		printf("%d\n",b[1].getID().VAO_ID);

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
