#include <stdio.h>
#include <stdlib.h>


#ifndef COMP_LIST_H
#define COMP_LIST_H

typedef struct comp_list_t 
{
  int node;
  struct comp_list_t *next;
} 
List;

List* list_init(void);
List* list_insert(List* list, int value);
void list_print(List* list);
List* list_lookup(List* list,int value);
List* list_remove(List* list,int value);


#endif
