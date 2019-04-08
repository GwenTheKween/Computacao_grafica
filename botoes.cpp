#include "botoes.h"

//======================================================================================================================
//Declaracao de metodos publicos

void botao::set(
		float* pos,
		unsigned int* index,
		unsigned int posCount,
		unsigned int indexCount,
		float* Color,
		void (*func)(void))
{
	color[0] = Color[0];
	color[1] = Color[1];
	color[2] = Color[2];
	position.resize(posCount*2);
	for(int i=0;i<posCount*2;i++){
		position[i] = pos[i];
	}
	action = func;
	ID.start(pos,index,posCount,2,indexCount,GL_TRIANGLES,GL_STATIC_DRAW,color);
}

bool botao::inside(int x, int y){
	if(getMaxX()>=x && x>=getMinX()){
		return (getMaxY()>= y && y >= getMinY());
	}
	return false;
}

void botao::disable(){
	active = false;
	float disColor[]={0.0f,0.0f,0.0f};
	ID.setColor(disColor);
}

void botao::enable(){
	active = true;
	ID.setColor(color);
}

float botao::getMinY(){
	if(minY>=0) return minY;
	else{
		minY = position[1];
		for(int i=1;i<position.size()/2;i++){
			if(minY > position[2*i + 1]){
				minY = position[2*i + 1];
			}
		}
	}
	return minY;
}

float botao::getMaxY(){
	if(maxY>=0) return maxY;
	else{
		maxY = position[1];
		for(int i=1;i<position.size()/2;i++){
			if(maxY < position[2*i + 1]){
				maxY = position[2*i + 1];
			}
		}
	}
	return maxY;
}

float botao::getMinX(){
	if(minX>=0) return minX;
	else{
		minX = position[0];
		for(int i=1;i<position.size()/2;i++){
			if(minX > position[2*i]){
				minX = position[2*i];
			}
		}
	}
	return minX;
}

float botao::getMaxX(){
	if(maxX>=0) return maxX;
	else{
		maxX = position[0];
		for(int i=1;i<position.size()/2;i++){
			if(maxX < position[2*i]){
				maxX = position[2*i];
			}
		}
	}
	return maxX;
}

float botao::getRed(){
	return color[0];
}

float botao::getGreen(){
	return color[1];
}

float botao::getBlue(){
	return color[2];
}

//======================================================================================================================
//declaracao de construtores
botao::botao(float* pos, unsigned int* ind, unsigned int posCount, unsigned int indCount, float* Color, void (*func)(void)):
	minX(-1),
	maxX(-1),
	minY(-1),
	maxY(-1),
	active(true)
{
	set(pos,ind,posCount,indCount,Color,func);
}

botao::botao():
	minX(-1),
	maxX(-1),
	minY(-1),
	maxY(-1),
	active(true)
{}

botao::~botao(){
}
