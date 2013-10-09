#include <stdio.h>
#include <stdlib.h>


#ifndef COMP_LIST_H
#define COMP_LIST_H

typedef struct comp_list_t 
{
  int type;
  int tam;
  char* text;
  struct comp_list_t *next;
} 
List;



List* list_init(void);
void list_print(List* list);
List* TILL_NULL(List* list);
List* FunctionParamList(List* AllParams, int function_id);
List* list_insert(List* list, int type,int tam, char* text);
List* list_lookup(List* list, char* text);
List* list_copy(List* list1, List* list2);
List* list_remove(List* list, char* text);


#endif
