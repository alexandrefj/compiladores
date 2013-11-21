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

	//FP_manager(root);

	generateCode(root); // gera o código em uma segunda passagem

  	return resultado;
}

