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

 List* list_create();
 List* list_insert(List *list, int data);

#endif
