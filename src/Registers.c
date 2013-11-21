#include "Registers.h"


int RegisterGenerate(int registers){
	if(registers==0)
		return 2;
	else
		return ++registers;
}


