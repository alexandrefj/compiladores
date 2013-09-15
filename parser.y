%{
#include <stdio.h>
#include <stdlib.h>
#include "main.h"

struct astreenode *root;
%}

%union
{
struct nome_interno *symbol;
int type;
struct astreenode *ast;
}

/*
%type<ast> program
%type<ast> function
%type<ast> local_var_decl
%type<ast> block
%type<ast> flow_block
%type<ast> simple_command_function
%type<ast> global_var_decl
%type<ast> simple_command
%type<ast> control_flow_command

%type<ast> return

%type<ast> param_list
%type<ast> call_param_list
%type<ast> exp
%type<ast> constant
%type<ast> output	
%type<ast> type 

*/
%token TK_PR_INT	256
%token TK_PR_FLOAT	257
%token TK_PR_BOOL	258
%token TK_PR_CHAR	259
%token TK_PR_STRING	260

%token TK_PR_IF		261
%token TK_PR_THEN	262
%token TK_PR_ELSE	263
%token TK_PR_WHILE	264
%token TK_PR_DO		265
%token TK_PR_INPUT	266
%token TK_PR_OUTPUT	267
%token TK_PR_RETURN	268
%token TK_OC_LE		270
%token TK_OC_GE		271
%token TK_OC_EQ		272
%token TK_OC_NE		273
%token TK_OC_AND	274
%token TK_OC_OR		275

%token TK_LIT_INT	281
%token TK_LIT_FLOAT	282
%token TK_LIT_FALSE	283
%token TK_LIT_TRUE	284
%token TK_LIT_CHAR	285
%token TK_LIT_STRING	286
%token TK_IDENTIFICADOR	290

%token TOKEN_ERRO	291




/*
%token<symbol> TK_LIT_INT   	1
%token<symbol> TK_LIT_FLOAT 	2
%token<symbol> TK_LIT_CHAR     	3
%token<symbol> TK_LIT_STRING   	4
%token<symbol> TK_LIT_BOOL   	5
%token<symbol> TK_IDENTIFICADOR	6
*/

%left TK_OC_LE TK_OC_GE TK_OC_EQ TK_OC_NE '=' '<' '>'
%left TK_OC_AND TK_OC_OR
%left '-' '+'
%left '*' '/'
%left ')'
%left ']'



%nonassoc TK_PR_THEN
%nonassoc TK_PR_ELSE

%%

/*******************************************************************************************
----------------------REGRAS DA LINGUAGEM IKS---------------------------------------------**
*******************************************************************************************/


programa:   funcao programa
	   |declaracao_var_globais programa
	   |
	   ;

funcao:    tipo ':' TK_IDENTIFICADOR '('parametros_funcao')' declaracao_var_locais '{' bloco '}' ;

parametros_funcao: 	tipo ':' TK_IDENTIFICADOR 
			| tipo ':'TK_IDENTIFICADOR ',' tipo ':' TK_IDENTIFICADOR parametros_funcao
			|
			;

declaracao_var_locais:  tipo ':' TK_IDENTIFICADOR';' declaracao_var_locais
			|
			;

declaracao_var_globais: tipo ':' TK_IDENTIFICADOR';' 		
			| tipo ':' TK_IDENTIFICADOR '['TK_LIT_INT']'';'
			;


tipo:                   TK_PR_INT
			|TK_PR_FLOAT
			|TK_PR_BOOL
			|TK_PR_STRING
			|TK_PR_CHAR
			;

comando:    TK_PR_IF '('condicao')'TK_PR_THEN comando
	   |TK_PR_IF '('condicao')'TK_PR_THEN comando TK_PR_ELSE comando
	   |TK_PR_WHILE '('condicao')'TK_PR_DO comando 
	   |TK_PR_DO comando TK_PR_WHILE'('condicao')' 
	   |TK_PR_INPUT TK_IDENTIFICADOR ';'
	   |atribuicao 	
	   |TK_PR_OUTPUT output ';' 
	   |TK_PR_RETURN expressao ';'
	   //|bloco
	   |chamada_funcao
	   |';'
	   ;

output:      saida
	   | saida ',' output
	   |
	   ;

bloco:         comando bloco
	      | '{' comando bloco '}' 
	      |
	      ;

  
atribuicao:   TK_IDENTIFICADOR '=' expressao';' 
	      |TK_IDENTIFICADOR'['expressao']' '=' expressao';'
	      ;

expressao:	TK_IDENTIFICADOR
		|literal
		| '(' expressao')'
        	//| '&' expressao 
        	| '*' expressao
		| expressao '+' expressao
		| expressao '*' expressao
		| expressao '/' expressao
		| expressao '-' expressao
		| '-' expressao
		| expressao TK_OC_LE expressao
		| expressao TK_OC_GE expressao
		| expressao TK_OC_EQ expressao
		| expressao TK_OC_NE expressao
		| expressao '>' expressao
		| expressao '<' expressao
		| expressao TK_OC_AND expressao
		| expressao TK_OC_OR expressao
		| TK_IDENTIFICADOR '[' expressao ']'
		| chamada_funcao
		;

chamada_funcao: TK_IDENTIFICADOR '(' chamada_recursao ')';

chamada_recursao:  expressao
		  | ',' chamada_recursao
		  |
		  ;
		


literal:                  TK_LIT_INT		
			//| '-'TK_LIT_INT 	
			| TK_LIT_FLOAT		
			//| '-'TK_LIT_FLOAT	
			| TK_LIT_STRING		
			| TK_LIT_CHAR		
			| TK_LIT_TRUE		
			| TK_LIT_FALSE		
			;

condicao:	TK_IDENTIFICADOR
		|literal
		| '(' condicao')'
        	//| '&' condicao 
        	| '*' condicao
		| condicao '+' condicao
		| condicao '*' condicao
		| condicao '/' condicao
		| condicao '-' condicao
		| '-' condicao
		| condicao TK_OC_LE condicao
		| condicao TK_OC_GE condicao
		| condicao TK_OC_EQ condicao
		| condicao TK_OC_NE condicao
		| condicao '>' condicao
		| condicao '<' condicao
		| condicao TK_OC_AND condicao
		| condicao TK_OC_OR condicao
		| TK_IDENTIFICADOR '['condicao']'
		| chamada_funcao
		;
		

saida:     	TK_IDENTIFICADOR
		|TK_LIT_STRING
		| '(' saida')'
        	//| '&' saida 
        	| '*' saida	
		| saida '+' saida
		| saida '*' saida
		| saida '/' saida
		| saida '-' saida
		| '-' saida
		| saida TK_OC_LE saida
		| saida TK_OC_GE saida
		| saida TK_OC_EQ saida
		| saida TK_OC_NE saida
		| saida '>' saida
		| saida '<' saida
		| saida TK_OC_AND saida
		| saida TK_OC_OR saida
		| TK_IDENTIFICADOR '['saida ']'
		| chamada_funcao
		;	 

%%


