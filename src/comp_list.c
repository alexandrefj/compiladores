#include <stdio.h>
#include <stdlib.h>
#include "comp_list.h"

List *list_create() {
  return NULL;
}

List* list_insert(List *list, int data) {

  List *new = malloc(sizeof(List));
  List *aux;
  
  new->node = data;
  new->next = NULL;

  if (list == NULL) {
	return new;
  } else {
	aux = list;
	while(aux->next != NULL)
		aux = aux->next;

    	aux->next = new;

	return list;
  }
}
