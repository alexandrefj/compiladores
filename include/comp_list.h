#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#ifndef COMP_LIST_H
#define COMP_LIST_H

typedef struct comp_list_t 
{
  int type;
  int tam;
  int size;
  char* text;
  struct comp_list_t *dim;
  struct comp_list_t *next;
} 
List;

typedef struct st_function_list
{
	char* name;
	struct st_function_list* next;
} FunctionList;

List* list_init(void);
//List* JoinGlobalVet(List* global,List* vet);
void list_print(List* list);
List* TILL_NULL(List* list);
List* FunctionParamList(List* AllParams, int function_id);
List* list_insert(List* list, int type,int tam, char* text,int size);
List* list_lookup(List* list, char* text);
List* list_copy(List* list1, List* list2);
List* list_remove(List* list, char* text);
List* InvertList(List* list);

FunctionList* functionListInit(void);
FunctionList* searchFunction(FunctionList* functionList, char* name);
FunctionList* insertFunction(FunctionList* functionList, char* name);


#endif
