#include "botoes.h"

//======================================================================================================================
//Declaracao de metodos publicos

void botao::set(
		float* pos,
		unsigned int* index,
		unsigned int posCount,
		unsigned int indexCount,
		void (*func)(void))
{
	float color[3] = {1.0f,1.0f,1.0f};
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
	ID.setColor(0.0f,0.0f,0.0f);
}

void botao::enable(){
	active = true;
	ID.setColor(1.0f,1.0f,1.0f);
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

//======================================================================================================================
//declaracao de construtores
botao::botao(float* pos, unsigned int* ind, unsigned int posCount, unsigned int indCount, void (*func)(void)):
	minX(-1),
	maxX(-1),
	minY(-1),
	maxY(-1),
	active(true)
{
	set(pos,ind,posCount,indCount,func);
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
