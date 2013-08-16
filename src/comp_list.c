#include<stdlib.h>
#include<stdio.h>
#include "comp_list.h"
#include <string.h>



List* list_init(void)
{
	List* list = malloc(sizeof(List*));
	list = NULL;
	return list;
}

List* list_insert(List* list, int value)
{

	List* new = malloc(sizeof(List*));
	new->node = value;
	new->next = NULL;

	if(list == NULL)
		list = new;
	else 				
	{
		List* aux = list;

		while(aux->next != NULL)
			aux = aux->next;

		aux->next = new;
	}	
	
	return list;

}

void list_print(List* list)
{
	List* aux = list;
	
	if(list!= NULL)
	{
		while(aux != NULL)
		{
			printf("value = %d\n", aux->node);
			aux = aux->next;
		}
	}
	else
		printf("EMPTY LIST\n");

}


List* list_lookup(List* list,int value)
{

	if(list == NULL)
		puts("Empty list");
	else 				
	{
		List* aux = list;

		while(aux != NULL)
		{	
			if(aux->node==value)
				return aux;

			aux = aux->next;
		}

		puts("value not found");

	}	


}

List* list_remove(List* list,int value)
{
	int found =0;

	if(list != NULL)				
	{
		List* aux = list;
		List* aux_ant = list;

		while(aux != NULL && !found)
		{	
			if(aux->node == value)
			{
				found = 1;

				if(aux==list && aux_ant==list && aux->next!=NULL)
				{
					list = aux->next;
					aux = NULL;
				}
				else if(aux==list && aux_ant==list && aux->next==NULL)
				{
					list = NULL;
					aux = NULL;
				}
				else if(aux->next==NULL && aux_ant==list)
				{
					aux_ant->next = aux->next;
					aux = NULL;
					list = aux_ant;
				}				
				else
				{
					aux_ant->next = aux->next;
					aux = NULL;
				}	
			}
				
			if(!found)
			{
				if(aux != list ) 		// at the first time, aux_ant wont be forwarded
					aux_ant = aux_ant->next;
				aux = aux->next;
			}
			
		}

	}	

	return list;
}
