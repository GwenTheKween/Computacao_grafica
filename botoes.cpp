#include "botoes.h"

//======================================================================================================================
//Declaracao de metodos publicos

void botao::set(float* pos, void (*func)(void)){
	for(int i=0;i<8;i++){
		position[i] = pos[i];
	}
	action = func;
	unsigned int ind[]={0,1,2,2,3,0};
	ID.set(pos,ind,4,2,6,GL_TRIANGLES);
}

bool botao::inside(int x, int y){
	if(getMaxX()>=x && x>=getMinX()){
		return (getMaxY()>= y && y >= getMinY());
	}
	return false;
}

//======================================================================================================================
//declaracao de construtores
botao::botao(float* pos, void (*func)(void)){
	set(pos,func);
}

