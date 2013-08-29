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

DICT* dict_insert(DICT* dictionary,int key_in, char* value_in, int type)
{

	DICT* new = malloc(sizeof(DICT*));
	char* value_new = malloc(sizeof(char*));

	strcpy(value_new,value_in);
	new->key = key_in;
	new->value = value_new;//value_new;
	new->type = type;
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
	
	return new;

}

void dict_print(DICT* dictionary)
{
	DICT* aux = dictionary;
	
	if(dictionary!= NULL)
	{	
		printf("_________________________________________________\n");
		while(aux != NULL)
		{	
			printf("|Linha = %d", aux->key);
			printf("    ");
			printf("caractere = %s", aux->value);
			printf("    ");
			printf("tipo = %d\n",aux->type);
			aux = aux->next;
		}
		printf("_________________________________________________\n");
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

DICT* dict_remove (DICT* dictionary,int key_in)
{
	DICT* ant = NULL; 
	DICT* p = dictionary; 
						
	while (p != NULL && p->key != key_in)
	{
		ant = p;
		p = p->next;
	}

	if (p == NULL)
		return dictionary;

	if (ant == NULL)
		dictionary = p->next;
	else		
		ant->next = p->next;


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
