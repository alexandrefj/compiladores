#include<stdlib.h>
#include<stdio.h>
#include "comp_dict.h"
#include <string.h>

int main()
{

	// ELEMENTS INSERTION
	// prototype:  dict_insert(key, value);

	dict_init();
	dict_insert("0","null");
	dict_insert("1","eins");
	dict_insert("2","zwei");
	dict_insert("3","drei");
	dict_insert("4","vier");
	dict_insert("5","funf");
	dict_insert("6","sechs");
	dict_insert("7","sieben");
	dict_insert("8","acht");
	dict_insert("9","neun");
	dict_insert("10","zehn");
	
	dict_print();

	// LOOKUP --------------------
	// prototype:  dict_lookup(key);
	printf("\nLOOKUP\n\n");
	printf("if key = 4 then value = %s\n",dict_lookup("4"));
	printf("if key = 5 then value = %s\n",dict_lookup("5"));
	printf("if key = 6 then value = %s\n",dict_lookup("6"));
	printf("if key = 7 then value = %s\n",dict_lookup("7"));

	printf("if key = 11 then value = %s\n",dict_lookup("11"));
	printf("if key = 55 then value = %s\n",dict_lookup("55"));

	// REMOVE --------------------
	// prototype:  dict_remove(key);
	printf("\nREMOVE\n\n");

	dict_remove("0");
	printf("\n");
	dict_print();
	dict_remove("10");
	printf("\n");
	dict_print();
	printf("\n");
	dict_remove("1");
	dict_remove("2");
	dict_remove("3");
	dict_remove("4");
	dict_print();
	printf("\n");
	dict_remove("5");
	dict_remove("6");
	dict_remove("7");
	dict_remove("8");
	dict_remove("9");
	dict_print();


	// ELEMENTS INSERTION
	// prototype:  dict_insert(key, value);

	dict_init();
	dict_insert("0","null");
	dict_insert("1","eins");
	dict_insert("2","zwei");
	dict_insert("3","drei");
	dict_insert("4","vier");
	dict_insert("5","funf");
	dict_insert("6","sechs");
	dict_insert("7","sieben");
	dict_insert("8","acht");
	dict_insert("9","neun");
	dict_insert("10","zehn");
	
	dict_print();


	// REPLACE --------------------
	// prototype:  dict_repace(key,newvalue);
	printf("\nREPLACE\n\n");
	dict_replace("0","zero");
	dict_replace("1","um");
	dict_replace("10","dez");
	dict_replace("15","dez");
	dict_replace("5","cinco");

	dict_print();


	return 0;
}
