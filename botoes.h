#ifndef BOTOES
#define BOTOES
#include "dm.h"

class botao{
private:
	VAO_INFO ID;
	std::vector<float> position;
	void (*action)(void);
	float maxX,minX,maxY,minY;

public:
	botao();
	botao(float*,unsigned int*, unsigned int, unsigned int, void (*func)(void));

	void set(float*,unsigned int*, unsigned int, unsigned int, void(*func)(void));

	void press(){
		action();
	}

	bool inside(int,int);

	VAO_INFO getID(){return ID;}

	float getMinY();
	float getMinX();
	float getMaxX();
	float getMaxY();
};

#endif
