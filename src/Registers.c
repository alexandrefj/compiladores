#include "Registers.h"


int RegisterGenerate(int registers){return ++registers;}
/*
REGISTER* RegInit(void){
	REGISTER* reg = (REGISTER*)calloc(1,sizeof(REGISTER*));
	reg = NULL;
	return reg;
}

REGISTER* CreateNewRegister(REGISTER* reg){
	REGISTER* new = malloc(sizeof(REGISTER*));
	new->id = 0;
	new->var =NULL;
	new->used = 0;
	//new->var_reg_id = 0;
	new->next = NULL;

	if(reg == NULL){ 
		return new;
	}
	else{
		new->id = reg->id + 1;
		new->next = reg;
		return new;
	}	
}

void ShowRegisters(REGISTER* reg){

	while(reg != NULL){
		printf("id = %d \n", reg->id);
		puts(reg->var);
		reg = reg->next; 
	}
}

REGISTER* VarRegisterCreate(List* VarList){
	REGISTER* RegisterVar = RegInit();
	REGISTER* aux= RegisterVar;
	while(VarList != NULL){
		REGISTER* new = malloc(sizeof(REGISTER*));
		new->id = 0;
		new->used = 0;
		//new->var_reg_id = 0;
		new->var=VarList->text;
		new->next = NULL;
		if(RegisterVar == NULL)
			RegisterVar = new;
		else{
			while(aux->next != NULL)
				aux = aux->next;
			new->id = -1;	This field will point to reglist id whose VarReg pointer has been initialized
			aux->next = new;
		}
		aux = RegisterVar;
		VarList = VarList->next;		
	}
	return RegisterVar;
}

REGISTER* RegLookUp(REGISTER* VarList, char* VarName)
{

	if(VarList == NULL)
		return NULL;
	else 				
	{
		REGISTER* aux = VarList;

		while(aux != NULL)
		{	
			if(strcmp(aux->var, VarName) == 0)
				return aux;
			else
				aux = aux->next;
		}

		return NULL;

	}	
}
*/

