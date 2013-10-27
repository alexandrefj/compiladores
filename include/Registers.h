#include <stdio.h>
#include <stdlib.h>
#include "comp_list.h"
//#include "iks_ast.h"
//#include "comp_tree.h"


#ifndef REGISTERS_H
#define REGISTERS_H




int RegisterGenerate(int registers);
/*
typedef struct reg {

	int id;
	int used;
	char* var;
	//int var_reg_id; /*points to the register thar has been loaded with a variable
	struct reg *next;

}REGISTER;



REGISTER* RegInit(void);
void ShowRegisters(REGISTER* reg);
REGISTER* CreateNewRegister(REGISTER* reg);
REGISTER* VarRegisterCreate(List* VarList);
REGISTER* RegLookUp(REGISTER* VarList, char* VarName);

*/
#endif
