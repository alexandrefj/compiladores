#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "comp_dict.h"
//#include "main.h"
#include "tokens.h"


#define IKS_SIMBOLO_INDEFINIDO 		0
#define IKS_SIMBOLO_LITERAL_INT 	1
#define IKS_SIMBOLO_LITERAL_FLOAT 	2
#define IKS_SIMBOLO_LITERAL_CHAR 	3
#define IKS_SIMBOLO_LITERAL_STRING 	4
#define IKS_SIMBOLO_LITERAL_BOOL 	5
#define IKS_SIMBOLO_IDENTIFICADOR 	6


DICT_NODE *Table[DICT_SIZE];

void removeBarra(char* str)
{
	int len,i,j;
	bool found = false;
	len = strlen(str);
	for (i = 0; i < len; ++i)
	{
		if (found){
			if ((str[i] == '\\') || (str[i] == '\"')) 
				for(j = i-1; j < len; ++j)
					str[j] = str[j+1];
			found = false;
		}
					
		else
			if(str[i] == '\\')
				found = true;
	}

}

void dict_init(void)
{
    int i;
    for(i=0;i<DICT_SIZE;i++)
        Table[i] = 0;
}

int dict_address(char* text)
{
    int address = 1;
    int i;

    for(i=0;i<strlen(text);++i)
        address = ((address*text[i])%DICT_SIZE)+1;
		
    return address-1;
}

DICT_NODE *dict_find(char *text)
{
	DICT_NODE *node;
	int address = dict_address(text);
	for(node = Table[address]; node != 0; node = node->next)
		if(!strcmp(text,node->text))
			return node;
	return 0;		
}

DICT_NODE *dict_insert(char *text, int type)
{
	DICT_NODE *node;
	int address = 0;
	int len;
	
	len = strlen(text);

	if(node = dict_find(text))
		return node;
		
	address = dict_address(text);
	node = (DICT_NODE*) calloc (1,sizeof(DICT_NODE));

	if (type != IKS_SIMBOLO_LITERAL_CHAR && type != IKS_SIMBOLO_LITERAL_STRING){
        	node->text = malloc(len + 1);
        	strcpy(node->text, text);
    	}
	else{
        	node->text = malloc(len - 2 + 1);
        	strncpy(node->text , text + 1, len - 2);
		removeBarra(node->text);
    	}

    	node->type = type;
    
    	node->intVal = 0;
    	node->charVal = ' ';
    	node->boolVal = 0;
    
    	switch (type) 
	{
        	case IKS_SIMBOLO_LITERAL_INT:
            	    				node->intVal = atoi(text);
            	    				break;
		case IKS_SIMBOLO_LITERAL_CHAR:
		    				node->charVal = text[1];
		    				break;
		case IKS_SIMBOLO_LITERAL_BOOL:
		    				if(strcmp(text,"false")==0) node->boolVal = 0;
	     				        else node->boolVal = 1;

		    				break;
		default:
		    				break;
    	}
	
	node->next = Table[address];
	Table[address] = node;
	
	return node;
	
}

void dict_print(void)
{
	int i;
	DICT_NODE *node;


	for(i=0;i< DICT_SIZE;i++)
	{
		for(node = Table[i]; node; node = node->next)
			{{
			printf("tipo %d texto %s ", node->type, node->text);
            		printf("int %d ", node->intVal);
            		printf("char %c ", node->charVal);
            		printf("bool %d\n", node->boolVal);
			}}		
	}

}
