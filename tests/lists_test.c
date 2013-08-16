#include <stdio.h>
#include <stdlib.h>
#include "comp_list.h"

int main()
{
	List* list = list_init();
	List* aux;

	list = list_insert(list, 0);
	list = list_insert(list, 1);
	list = list_insert(list, 2);
	list = list_insert(list, 3);
	list = list_insert(list, 4);
	list = list_insert(list, 5);
	list = list_insert(list, 6);
	list = list_insert(list, 7);
	list = list_insert(list, 8);
	list = list_insert(list, 9);
	list = list_insert(list, 10);
	list = list_insert(list, 11);
	list_print(list);

	aux = list_lookup(list,3);
	printf("|LOOKUP TEST\n");
	printf("value = %d, value->next = %d\n", aux->node, aux->next->node);

	list = list_remove(list,1);
	list = list_remove(list,2);
	list = list_remove(list,3);
	list = list_remove(list,5);
	list = list_remove(list,6);
	list = list_remove(list,7);
	
	list_print(list);
	printf("\n");
	list = list_remove(list,11);
	list = list_remove(list,4);
	list = list_remove(list,0);
	list = list_remove(list,9);
	list = list_remove(list,10);
	list = list_remove(list,11);
	list = list_remove(list,15);
	list = list_remove(list,8);

	list_print(list);



return 0;

}
