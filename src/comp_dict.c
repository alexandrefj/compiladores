#include<stdlib.h>
#include<stdio.h>
#include "comp_dict.h"
#include <string.h>

DICT* dictionary;

void dict_init()
{
	dictionary = malloc(sizeof(DICT*));
	dictionary = NULL;
}

void dict_insert(char* key_in, char* value_in)
{

	DICT* new = malloc(sizeof(DICT*));
	new->key = key_in;
	new->value = value_in;
	new->next = NULL;

	if(dictionary == NULL)
		dictionary = new;
	else 				// Has already nodes
	{
		DICT* aux = dictionary;

		while(aux->next != NULL)
			aux = aux->next;

		aux->next = new;
	}	


}

void dict_print(void)
{
	DICT* aux = dictionary;
	
	if(dictionary!= NULL)
	{
		while(aux != NULL)
		{
			printf(" key = %s - value = %s\n", aux->key, aux->value);
			aux = aux->next;
		}
	}
	else
		printf("EMPTY DICTIONARY\n");

}

char* dict_lookup(char* key_in)
{

	if(dictionary == NULL)
		return "Empty dictionary";
	else 				
	{
		DICT* aux = dictionary;

		while(aux != NULL)
		{	
			if(strcmp(aux->key,key_in) == 0)
				return aux->value;

			aux = aux->next;
		}

		return "key not found";

	}	


}

void dict_remove(char* key_in)
{
	int found =0;

	if(dictionary != NULL)				
	{
		DICT* aux = dictionary;
		DICT* aux_ant = dictionary;

		while(aux != NULL && !found)
		{	
			if(strcmp(aux->key,key_in) == 0)
			{
				found = 1;

				if(aux==dictionary && aux_ant==dictionary && aux->next!=NULL)
				{
					dictionary = aux->next;
					aux = NULL;
				}
				else if(aux==dictionary && aux_ant==dictionary && aux->next==NULL)
				{
					dictionary = NULL;
					aux = NULL;
				}
				else if(aux->next==NULL && aux_ant==dictionary)
				{
					aux_ant->next = aux->next;
					aux = NULL;
					dictionary = aux_ant;
				}				
				else
				{
					aux_ant->next = aux->next;
					aux = NULL;
				}	
			}
				
			if(!found)
			{
				if(aux != dictionary ) 		// at the first time, aux_ant wont be forwarded
					aux_ant = aux_ant->next;
				aux = aux->next;
			}
			
		}

	}	


}

void dict_replace(char* key_in,char* value_in)
{
	int found = 0;

	if(dictionary == NULL)
		puts("Empty dictionary");
	else 				
	{
		DICT* aux = dictionary;

		while(aux != NULL && !found)
		{	
			if(strcmp(aux->key,key_in) == 0){
				aux->value = value_in;
				found = 1;}

			aux = aux->next;
		}
		if(!found)
			puts("key not found");

	}	


}
