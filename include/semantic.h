#include <stdio.h>
#include <stdlib.h>
#include "erros_semanticos.h"
#include <comp_tree.h>
#include <comp_list.h>
#include <comp_dict.h>
#include <stack.h>


#ifndef SEMANTIC_H
#define SEMANTIC_H

#define IKS_INT 	 1
#define IKS_FLOAT 	 2
#define IKS_CHAR	 3
#define IKS_STRING	 4
#define IKS_BOOL	 5


#define GLOBAL_VAR_DEC_IDENTIFIER_CONTROL 	1
#define	GLOBAL_VET_DEC_IDENTIFIER_CONTROL	2
#define	LOCAL_VAR_DEC_IDENTIFIER_CONTROL	3
#define	FUNCTION_IDENTIFIER_CONTROL		4
#define	FUNCTION_VAR_IDENTIFIER_CONTROL		5
#define	INPUT_IDENTIFIER_CONTROL		6
#define ATRIBUICAO_IDENTIFIER_CONTROL		7
#define CHAMADA_FUNC_IDENTIFIER_CONTROL		8



void StackPopCommands(STACK* stack, List* global,List* global_vet, List* local,List* function_list, List* AllParams);
ASTREE* ParamLookup(ASTREE* param_i, List* param_list);
List* FunctionListInsert(List* function_list,DICT_NODE* node, int type, int size, int label);
List* GlobalVarListInsert(List* global_var,DICT_NODE* node,int control,int type, int size);
List* LocalVarListInsert(List* local_var,DICT_NODE* node, int type, int size,List* function_list);
int inference(int val1, int val2);
int inference_three(int val1, int val2);
int var_size(int id);



#endif
