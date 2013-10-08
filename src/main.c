/*
   main.c

   Arquivo principal do analisador sintático.
*/
#include "main.h"

/*
typedef struct ast{
	int teste;
}AST;
*/

void yyerror (char const *mensagem)
{
  fprintf (stderr, "%s\n", mensagem);
}

int main (int argc, char **argv)
{
   stack_pointer=stack_init();
   //aux = stack_pointer;
   global_var = list_init();
   global_vet = list_init();
   local_var = list_init();
   function_list = list_init();

  
   int resultado = yyparse();


  gv_init("saida.dot");
  astReadTree(root);
  gv_close();
/*
  puts("");
  list_print(global_var);
  puts("");
  list_print(local_var);
  puts("");
  list_print(global_vet);
  puts("");
  list_print(function_list);
*/


  return resultado;
}

