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
  
  //AST* testando1,*testando2;

  
  int resultado = yyparse();

	/*printf("type:%d\n",root->type);
	root=root->scc[0];
	printf("type:%d\n",root->type);
	root=root->scc[0];
	printf("type:%d\n",root->type);
	root=root->scc[0];
	printf("type:%d ",root->type); printf("%s\n", root->symbol->text);
	root=root->scc[0];
	printf("type:%d\n",root->type);
*/


gv_init("saida.dot");astReadTree(root);gv_close();
//gv_init("saida.dot");
 // astReadTree(root);
 // gv_close();

	//printf("%d\n"root->scc[0])

 // gv_declare (const int tipo, const void *pointer, char *name)
  //gv_declare (IKS_AST_IDENTIFICADOR,testando1, "var");
 // gv_declare (IKS_AST_IDENTIFICADOR,testando2, "variable");
  //void gv_connect (const void *p1, const void *p2)
  //gv_connect (testando1, testando2);

  return resultado;
}

