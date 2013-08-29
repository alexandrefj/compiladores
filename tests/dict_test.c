#include<stdlib.h>
#include<stdio.h>
#include "comp_dict.h"
#include <string.h>

int main()
{
	DICT* dictionary;
	// ELEMENTS INSERTION
	// prototype:  dict_insert(key, value);

	dictionary = dict_init();
	dictionary = dict_insert(dictionary,0,"null",2);
	dict_insert(dictionary,1,"eins",2);
	dict_insert(dictionary,2,"zwei",2);
	dict_insert(dictionary,3,"drei",2);
	dict_insert(dictionary,4,"vier",2);
	dict_insert(dictionary,5,"funf",2);
	dict_insert(dictionary,6,"sechs",2);
	dict_insert(dictionary,7,"sieben",2);
	dict_insert(dictionary,8,"acht",2);
	dict_insert(dictionary,9,"neun",2);
	dict_insert(dictionary,10,"zehn",2);
	
	dict_print(dictionary);

	// LOOKUP --------------------
	// prototype:  dict_lookup(key);
	printf("\nLOOKUP\n\n");
	printf("if key = 4 then value = %s\n",dict_lookup(dictionary,4));
	printf("if key = 5 then value = %s\n",dict_lookup(dictionary,5));
	printf("if key = 6 then value = %s\n",dict_lookup(dictionary,6));
	printf("if key = 7 then value = %s\n",dict_lookup(dictionary,7));

	printf("if key = 11 then value = %s\n",dict_lookup(dictionary,11));
	printf("if key = 55 then value = %s\n",dict_lookup(dictionary,55));

	// REMOVE --------------------
	// prototype:  dict_remove(key);
	printf("\nREMOVE\n\n");

	dictionary = dict_remove(dictionary,0);
	printf("\n");
	dict_print(dictionary);
	dictionary = dict_remove(dictionary,10);
	printf("\n");
	dict_print(dictionary);
	printf("\n");
	dictionary = dict_remove(dictionary,1);
	dictionary = dict_remove(dictionary,2);
	dictionary = dict_remove(dictionary,3);
	dictionary = dict_remove(dictionary,4);
	dict_print(dictionary);
	printf("\n");
	dictionary = dict_remove(dictionary,5);
	dictionary = dict_remove(dictionary,6);
	dictionary = dict_remove(dictionary,7);
	dictionary = dict_remove(dictionary,8);
	dictionary = dict_remove(dictionary,9);
	dict_print(dictionary);


	// ELEMENTS INSERTION
	// prototype:  dict_insert(key, value);

	dictionary = dict_insert(dictionary,0,"null",2);
	dict_insert(dictionary,1,"eins",2);
	dict_insert(dictionary,2,"zwei",2);
	dict_insert(dictionary,3,"drei",2);
	dict_insert(dictionary,4,"vier",2);
	dict_insert(dictionary,5,"funf",2);
	dict_insert(dictionary,6,"sechs",2);
	dict_insert(dictionary,7,"sieben",2);
	dict_insert(dictionary,8,"acht",2);
	dict_insert(dictionary,9,"neun",2);
	dict_insert(dictionary,10,"zehn",2);
	
	dict_print(dictionary);


	// REPLACE --------------------
	// prototype:  dict_repace(key,newvalue);
	printf("\nREPLACE\n\n");
	dict_replace(dictionary,0,"zero");
	dict_replace(dictionary,1,"um");
	dict_replace(dictionary,10,"dez");
	dict_replace(dictionary,15,"dez");
	dict_replace(dictionary,5,"cinco");

	dict_print(dictionary);


	return 0;
}
