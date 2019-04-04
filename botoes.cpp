#include "botoes.h"

//======================================================================================================================
botao::botao(float* pos, void (*func)(void)){
	for(int i=0;i<8;i++){
		position[i] = pos[i];
	}
	action = func;
}

