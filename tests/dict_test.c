#include<stdlib.h>
#include<stdio.h>
#include "comp_dict.h"
#include <string.h>

#define MaxSize 997

int main()
{
	DICT_NODE* Tabela[MaxSize];
	DICT_NODE* teste;

	dict_init(Tabela);
	teste=dict_insert("EU",1,Tabela);
	teste=dict_insert("QUERO",1,Tabela);
	teste=dict_insert("NEVE",1,Tabela);
	teste=dict_insert("NO",1,Tabela);
	teste=dict_insert("VERAO",1,Tabela);
	teste=dict_insert("EU",1,Tabela);
	dict_print(Tabela);
	
	DICT_NODE* aux = dict_find("EU",Tabela);

	printf("TEXTO ENCONTRADO: %s\n", aux->text);




	

	return 0;
}
