#include "comp_function.h"

FUNC* FuncInit(void){

	FUNC* func =  malloc(sizeof(FUNC*));
	func = NULL;
	return func;

}



FUNC* FuncInsert(FUNC* function, int type, char* text){

	FUNC* new =  malloc(sizeof(FUNC*));
	new->type = type;
	new->text = text;
	new->param = NULL;
	new->next = NULL;

	if(function == NULL)
		function = new;
	else 				
	{
		FUNC* aux = function;

		while(aux->next != NULL)
			aux = aux->next;

		aux->next = new;
	}	
	
	return function;

}

FUNC* ParamInsert(FUNC* function, int p_type, char* p_text){

	PARAM* new =  malloc(sizeof(FUNC*));
	new->p_type = p_type;
	new->p_text = p_text;
	new->next = NULL;
puts("aaa");
	if(function->param == NULL)
		function->param = new;
	else 				
	{
		PARAM* aux = function->param;

		while(aux->next != NULL)
			aux = aux->next;

		aux->next = new;
	}	
	

	return function;

}


FUNC* FuncPrint(FUNC* function){

	FUNC* aux = function;
	
	if(function!= NULL)
	{
		while(aux != NULL)
		{
			printf("type = %d ", aux->type);
			printf("text = %s\n", aux->text);
			aux = aux->next;
		}
	}
	else
		printf("EMPTY LIST\n");


}


