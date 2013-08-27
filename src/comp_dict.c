#include<stdlib.h>
#include<stdio.h>
#include "comp_dict.h"
#include <string.h>



DICT* dict_init()
{
	DICT* dictionary = malloc(sizeof(DICT*));
	dictionary = NULL;
	return dictionary;
}

DICT* dict_insert(DICT* dictionary,int key_in, char* value_in)
{

	DICT* new = malloc(sizeof(DICT*));
	char* value_new = malloc(sizeof(char*));
	strcpy(value_new,value_in);
	new->key = key_in;
	new->value = value_new;//value_new;
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
	
	return dictionary;

}

void dict_print(DICT* dictionary)
{
	DICT* aux = dictionary;
	
	if(dictionary!= NULL)
	{
		while(aux != NULL)
		{
			printf(" key = %d - value = %s\n", aux->key, aux->value);
			aux = aux->next;
		}
	}
	else
		printf("EMPTY DICTIONARY\n");

}

char* dict_lookup(DICT* dictionary,int key_in)
{

	if(dictionary == NULL)
		return "Empty dictionary";
	else 				
	{
		DICT* aux = dictionary;

		while(aux != NULL)
		{	
			if(aux->key == key_in)
				return aux->value;

			aux = aux->next;
		}

		return "key not found";

	}	


}

DICT* dict_remove(DICT* dictionary,int key_in)
{
	int found =0;

	if(dictionary != NULL)				
	{
		DICT* aux = dictionary;
		DICT* aux_ant = dictionary;

		while(aux != NULL && !found)
		{	
			if(dictionary->key == key_in)
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

	return dictionary;
}

DICT* dict_replace(DICT* dictionary,int key_in,char* value_in)
{
	int found = 0;

	if(dictionary == NULL)
		puts("Empty dictionary");
	else 				
	{
		DICT* aux = dictionary;

		while(aux != NULL && !found)
		{	
			if(aux->key==key_in){
				aux->value = value_in;
				found = 1;}

			aux = aux->next;
		}
		if(!found)
			puts("key not found");

	}	

	return dictionary;
}
