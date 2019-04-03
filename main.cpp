#include "dm.h"

int main(){
	DisplayManager dm;
	try{
		dm.init(800,600);
		dm.run();
	}catch (std::exception& e){
		std::cerr << e.what() <<std::endl;
	}
	return 0;
}
