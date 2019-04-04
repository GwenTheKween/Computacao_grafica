#ifndef BOTOES
#define BOTOES
#include "dm.h"

class botao{
private:
	VAO_INFO ID;
	float position[8];
	void (*action)(void);

	float getMaxX(){
		return (position[0] == position[2]) ? //checa se a primeira e segunda coordenada X sao iguais
					(position[0] > position[4]) ? position[0]:position[4]://se for, retorna o maior entre a primeira e a terceira coord
					(position[0] > position[2]) ? position[0]:position[2];//se nao for, retorna o maior entre a primeira e a segunda coord
	}


	float getMinX(){
		return (position[0] == position[2]) ? //checa se a primeira e segunda coordenada X sao iguais
					(position[0] < position[4]) ? position[0]:position[4]://se for, retorna a menor entre a primeira e a terceira coord
					(position[0] < position[2]) ? position[0]:position[2];//se nao for, retorna a menor entre a primeira e a segunda coord
	}


	float getMaxY(){
		return (position[1] == position[3]) ? //checa se a primeira e segunda coordenada X sao iguais
					(position[1] > position[5]) ? position[1]:position[5]://se for, retorna o maior entre a primeira e a terceira coord
					(position[1] > position[5]) ? position[1]:position[3];//se nao for, retorna o maior entre a primeira e a segunda coord
	}



	float getMinY(){
		return (position[1] == position[3]) ? //checa se a primeira e segunda coordenada X sao iguais
					(position[1] < position[5]) ? position[1]:position[5]://se for, retorna o maior entre a primeira e a terceira coord
					(position[1] < position[3]) ? position[1]:position[3];//se nao for, retorna o maior entre a primeira e a segunda coord
	}


public:
	botao(){};
	botao(float*, void (*func)(void));

	void set(float*, void(*func)(void));

	void press(){
		action();
	}

	bool inside(int,int);

	VAO_INFO getID(){return ID;}
};

#endif
