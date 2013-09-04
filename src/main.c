/*
   main.c

   Arquivo principal do analisador sintático.
*/
#include "main.h"

void yyerror (char const *mensagem)
{
  fprintf (stderr, "%s, Linha = %d\n", mensagem, getLineNumber());
}

int main (int argc, char **argv)
{
  int resultado = yyparse();
  printf("resultado = %d\n", resultado);
	//dict_print();
  return resultado;
}

