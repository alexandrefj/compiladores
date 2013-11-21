#include <stdio.h>
#include <stdlib.h>
#include "comp_function.h"

int main()
{

	FUNC* function;
	PARAM* parameter;

	function = FuncInit();

	printf("Ponteiro retornado por init = %p tamanho %lu bytes\n",function, sizeof(function));

	function = FuncInsert(function,1,"EU");
	function = FuncInsert(function,2,"QUERO");
	function = FuncInsert(function,3,"NEVE");
	function = FuncInsert(function,4,"NO");
	function = FuncInsert(function,5,"VERAO");

	FuncPrint(function);

	//parameter = ParamInsert(parameter,1,"param1");

	return 0;

}
