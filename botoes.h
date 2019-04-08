#ifndef BOTOES
#define BOTOES
#include "dm.h"

class botao{
private:
	VAO_INFO ID;
	std::vector<float> position;
	void (*action)(void);
	float maxX,minX,maxY,minY;
	bool active;
	float color[3];

public:
	botao();
	botao(float*,unsigned int*, unsigned int, unsigned int, float*, void (*func)(void));
	~botao();

	void set(float*,unsigned int*, unsigned int, unsigned int, float*, void(*func)(void));

	void press(){
		if(active) action();
	}

	bool inside(int,int);
	void disable();
	void enable();

	VAO_INFO getID(){return ID;}

	float getMinY();
	float getMinX();
	float getMaxX();
	float getMaxY();

	float getRed();
	float getGreen();
	float getBlue();
};

#endif
