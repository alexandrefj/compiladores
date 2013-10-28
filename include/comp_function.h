#include <stdio.h>
#include <stdlib.h>


#ifndef COMP_FUNCTION_H
#define COMP_FUNCTION_H

typedef struct function 
{
  int type;
  char* text;
  struct function *next;
  struct param * param;
} 
FUNC;

typedef struct param 
{
  int p_type;
  char* p_text;
  struct param *next;
} 
PARAM;



FUNC* FuncInit(void);
FUNC* FuncInsert(FUNC* function, int type, char* text);
FUNC* FuncPrint(FUNC* function);
FUNC* ParamInsert(FUNC* func, int p_type, char* p_text);

/*List* TILL_NULL(List* list);

List* list_insert(List* list, int type,int tam, char* text);
void list_print(List* list);
List* list_lookup(List* list, char* text);
List* list_copy(List* list1, List* list2);
List* list_remove(List* list, char* text);

*/
#endif