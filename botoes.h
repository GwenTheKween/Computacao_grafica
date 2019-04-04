#ifndef BOTOES
#define BOTOES
#include "dm.h"

class botao{
private:
	VAO_INFO ID;
	float position[8];
	void (*action)(void);
public:
	botao(){};
	botao(float*, void (*func)(void));

	void press(){
		action();
	}
};

#endif
