/*
  main.h

  Cabeçalho principal do analisador sintático
*/
#ifndef __MAIN_H
#define __MAIN_H

#include <stdio.h>
#include "comp_dict.h"
#include "comp_list.h"
#include "comp_tree.h"
#include "comp_graph.h"
#include "CodeGenerator.h"
#include "iks_ast.h"
#include "gv.h"
#include "stack.h"
#include "CodeGenerator.h"
//#include "CodeGenerator.h"



ASTREE *root;
STACK* stack_pointer;

TAC* code;
List *global_var;
List *global_vet;
List *local_var;
List *function_list;
List* param_list;
List* aux;
List* aux2;
List* global_code;
List* local_code;
FunctionList* functionList;
int func_id;
int type;
int func_type;
int array_el;
char* FuncString;


/*
  Constantes a serem utilizadas como valor de retorno no caso de
  sucesso (IKS_SYNTAX_SUCESS) e erro (IKS_SYNTAX_ERRO) do analisador
  sintático.
*/
#define IKS_SYNTAX_SUCESSO 0
#define IKS_SYNTAX_ERRO    1

/*
  Constantes a serem utilizadas para diferenciar os lexemas que estão
  registrados na tabela de símbolos.
*/
#define IKS_SIMBOLO_INT    1
#define IKS_SIMBOLO_FLOAT  2
#define IKS_SIMBOLO_CHAR   3
#define IKS_SIMBOLO_STRING 4
#define IKS_SIMBOLO_BOOL   5

#endif
