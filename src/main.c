/*
   main.c

   Arquivo principal do analisador sintático.
*/
#include "main.h"

void yyerror (char const *mensagem)
{
  	fprintf (stderr, "%s\n", mensagem);
}

int main (int argc, char **argv)
{

  	int resultado = yyparse();

  	gv_init("saida.dot");
  	astReadTree(root);
  	gv_close();


	//TAC_gen(local_var,global_var,global_vet,root);

  	return resultado;
}

