#include <stdio.h>
#include <stdlib.h>
#include "comp_list.h"

int main()
{
	int a = 5;
	List* lista = list_create();
	
	lista = list_insert(lista, a);
	a++;
	lista = list_insert(lista, a);
	a++;
	lista = list_insert(lista, a);

	
	printf("Nodo[%d]->%d\n", 0,lista->node);
	lista = lista->next;
	printf("Nodo[%d]->%d\n", 1,lista->node);
	lista = lista->next;
	printf("Nodo[%d]->%d\n", 2,lista->node);
	


return 0;

}