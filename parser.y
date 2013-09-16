%{
#include <stdio.h>
#include <stdlib.h>
#include "main.h"

//struct astreenode *root;
%}

%union
{
struct nome_interno *symbol;
int type;
struct astreenode *ast;
}


%type<ast> programa
%type<ast> funcao
%type<ast> comando
%type<ast> output
%type<ast> bloco
%type<ast> atribuicao
%type<ast> expressao
%type<ast> chamada_funcao
%type<ast> chamada_recursao
%type<ast> literal
%type<ast> condicao
%type<ast> saida


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

%token<symbol> TK_LIT_INT	281
%token<symbol> TK_LIT_FLOAT	282
%token<symbol> TK_LIT_FALSE	283
%token<symbol> TK_LIT_TRUE	284
%token<symbol> TK_LIT_CHAR	285
%token<symbol> TK_LIT_STRING	286
%token<symbol> TK_IDENTIFICADOR	290

%token TOKEN_ERRO	291

%left TK_OC_LE TK_OC_GE TK_OC_EQ TK_OC_NE '=' '<' '>'
%left TK_OC_AND TK_OC_OR
%left '-' '+'
%left '*' '/'
%left ')'
%left ']'

//%start funcao

%nonassoc TK_PR_THEN
%nonassoc TK_PR_ELSE

%%

/*******************************************************************************************
----------------------REGRAS DA LINGUAGEM IKS---------------------------------------------**
*******************************************************************************************/

programa:   funcao programa			{root = astCreate(IKS_AST_PROGRAMA, NULL, $1, $2, NULL, NULL);}
	   |declaracao_var_globais programa	{$$=astCreate(IKS_AST_PROGRAMA, NULL, $2,NULL, NULL, NULL);}//{root= $2;}
	   |{$$=NULL;}
	   ;

funcao:    tipo ':' TK_IDENTIFICADOR '('parametros_funcao')' declaracao_var_locais '{' bloco '}'{$$ = astCreate(IKS_AST_FUNCAO, $3, $9, 0, NULL, NULL);};

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

comando:    TK_PR_IF '('condicao')'TK_PR_THEN comando	{$$ = $6;}
	   |TK_PR_IF '('condicao')'TK_PR_THEN comando TK_PR_ELSE comando {$$ = astCreate(IKS_AST_IF_ELSE, NULL, $3, $8, NULL, NULL);}
	   |TK_PR_WHILE '('condicao')'TK_PR_DO comando 	{$$ = astCreate(IKS_AST_WHILE_DO, NULL, $3, $6, NULL, NULL);}
	   |TK_PR_DO comando TK_PR_WHILE'('condicao')' 	{$$ = astCreate(IKS_AST_DO_WHILE, NULL, $2, $5, NULL, NULL);}
	   |TK_PR_INPUT TK_IDENTIFICADOR ';'	       	{$$ = astCreate(IKS_AST_INPUT, $2, NULL, NULL, NULL, NULL);}
	   |atribuicao 				       	{$$=$1;}
	   |TK_PR_OUTPUT output ';' 		       	{$$=$2;}
	   |TK_PR_RETURN expressao ';'			{$$ = astCreate(IKS_AST_RETURN, NULL, $2, NULL, NULL, NULL);}
	   |chamada_funcao				{$$ = $1;}
	   |';'						{$$ = NULL;}
	   ;

output:      saida					{$$ = astCreate(IKS_AST_OUTPUT, NULL, $1, NULL, NULL, NULL);}
	   | saida ',' output				{$$ = astCreate(IKS_AST_OUTPUT, NULL, $1, $3, NULL, NULL);}
	   |{$$=NULL;}
	   ;

bloco:         comando bloco		{$$ = astCreate(IKS_AST_BLOCO, NULL, $1, $2, NULL, NULL);}	
	      | '{' comando bloco '}' 	{$$ = astCreate(IKS_AST_BLOCO, NULL, $2, $3, NULL, NULL);}
	      | {$$=NULL;}
	      ;

  
atribuicao:   TK_IDENTIFICADOR '=' expressao';' 		{$$ = astCreate(IKS_AST_ATRIBUICAO,$1, $3, NULL, NULL, NULL);}
	      |TK_IDENTIFICADOR'['expressao']' '=' expressao';'	{$$ = astCreate(IKS_AST_ATRIBUICAO,NULL, $3, $6, NULL, NULL);}
	      ;

expressao:	TK_IDENTIFICADOR			{$$ = astCreate(IKS_AST_IDENTIFICADOR, $1, NULL, NULL, NULL, NULL);}
		|literal				{$$ = $1;}
		| '(' expressao')'			{$$ = $2;}
        	| '*' expressao				{$$ = $2;}
		| expressao '+' expressao		{$$ = astCreate(IKS_AST_ARIM_SOMA,NULL, $1, $3, NULL, NULL);}
		| expressao '*' expressao		{$$ = astCreate(IKS_AST_ARIM_MULTIPLICACAO,NULL, $1, $3, NULL, NULL);}
		| expressao '/' expressao		{$$ = astCreate(IKS_AST_ARIM_DIVISAO,NULL, $1, $3, NULL, NULL);}
		| expressao '-' expressao		{$$ = astCreate(IKS_AST_ARIM_SUBTRACAO,NULL, $1, $3, NULL, NULL);}
		| '-' expressao				{$$ = astCreate(IKS_AST_ARIM_INVERSAO,NULL, $2, NULL, NULL, NULL);}
		| expressao TK_OC_LE expressao		{$$ = astCreate(IKS_AST_LOGICO_COMP_LE,NULL, $1, $3, NULL, NULL);}
		| expressao TK_OC_GE expressao		{$$ = astCreate(IKS_AST_LOGICO_COMP_GE,NULL, $1, $3, NULL, NULL);}
		| expressao TK_OC_EQ expressao		{$$ = astCreate(IKS_AST_LOGICO_COMP_IGUAL,NULL, $1, $3, NULL, NULL);}
		| expressao TK_OC_NE expressao		{$$ = astCreate(IKS_AST_LOGICO_COMP_DIF,NULL, $1, $3, NULL, NULL);}
		| expressao '>' expressao		{$$ = astCreate(IKS_AST_LOGICO_COMP_G,NULL, $1, $3, NULL, NULL);}
		| expressao '<' expressao		{$$ = astCreate(IKS_AST_LOGICO_COMP_L,NULL, $1, $3, NULL, NULL);}
		| expressao TK_OC_AND expressao		{$$ = astCreate(IKS_AST_LOGICO_E,NULL, $1, $3, NULL, NULL);}
		| expressao TK_OC_OR expressao		{$$ = astCreate(IKS_AST_LOGICO_OU,NULL, $1, $3, NULL, NULL);}
		| TK_IDENTIFICADOR '[' expressao ']'	{$$ = astCreate(IKS_AST_VETOR_INDEXADO,$1, $3, NULL, NULL, NULL);}
		| chamada_funcao			{$$ = $1;}
		;

chamada_funcao: TK_IDENTIFICADOR '(' chamada_recursao ')' {$$ = astCreate(IKS_AST_CHAMADA_DE_FUNCAO, $1, $3, NULL, NULL, NULL);};

chamada_recursao:  expressao			{$$=$1;}
		  | ',' chamada_recursao	{$$=$2;}
		  |{$$=NULL;}
		  ;
		


literal:                  TK_LIT_INT	{$$ = astCreate(IKS_AST_LITERAL, $1, NULL, NULL, NULL, NULL); }		
			| TK_LIT_FLOAT	{$$ = astCreate(IKS_AST_LITERAL, $1, NULL, NULL, NULL, NULL);}
			| TK_LIT_STRING	{$$ = astCreate(IKS_AST_LITERAL, $1, NULL, NULL, NULL, NULL);}	
			| TK_LIT_CHAR	{$$ = astCreate(IKS_AST_LITERAL, $1, NULL, NULL, NULL, NULL);}
			| TK_LIT_TRUE	{$$ = astCreate(IKS_AST_LITERAL, $1, NULL, NULL, NULL, NULL);}	
			| TK_LIT_FALSE	{$$ = astCreate(IKS_AST_LITERAL, $1, NULL, NULL, NULL, NULL);}	
			;

condicao:	TK_IDENTIFICADOR		{$$ = astCreate(IKS_AST_IDENTIFICADOR, $1, NULL, NULL, NULL, NULL);}
		|literal			{$$=$1;}
		| '(' condicao')'		{$$=$2;}
        	| '*' condicao			{$$=$2;}
		| condicao '+' condicao		{$$ = astCreate(IKS_AST_ARIM_SOMA,NULL, $1, $3, NULL, NULL);}
		| condicao '*' condicao		{$$ = astCreate(IKS_AST_ARIM_MULTIPLICACAO,NULL, $1, $3, NULL, NULL);}
		| condicao '/' condicao		{$$ = astCreate(IKS_AST_ARIM_DIVISAO,NULL, $1, $3, NULL, NULL);}
		| condicao '-' condicao		{$$ = astCreate(IKS_AST_ARIM_SUBTRACAO,NULL, $1, $3, NULL, NULL);}
		| '-' condicao			{$$ = astCreate(IKS_AST_ARIM_INVERSAO,NULL, $2, NULL, NULL, NULL);}
		| condicao TK_OC_LE condicao	{$$ = astCreate(IKS_AST_LOGICO_COMP_LE,NULL, $1, $3, NULL, NULL);}
		| condicao TK_OC_GE condicao	{$$ = astCreate(IKS_AST_LOGICO_COMP_GE,NULL, $1, $3, NULL, NULL);}
		| condicao TK_OC_EQ condicao	{$$ = astCreate(IKS_AST_LOGICO_COMP_IGUAL,NULL, $1, $3, NULL, NULL);}
		| condicao TK_OC_NE condicao	{$$ = astCreate(IKS_AST_LOGICO_COMP_DIF,NULL, $1, $3, NULL, NULL);}
		| condicao '>' condicao		{$$ = astCreate(IKS_AST_LOGICO_COMP_G,NULL, $1, $3, NULL, NULL);}
		| condicao '<' condicao		{$$ = astCreate(IKS_AST_LOGICO_COMP_L,NULL, $1, $3, NULL, NULL);}
		| condicao TK_OC_AND condicao	{$$ = astCreate(IKS_AST_LOGICO_E,NULL, $1, $3, NULL, NULL);}
		| condicao TK_OC_OR condicao	{$$ = astCreate(IKS_AST_LOGICO_OU,NULL, $1, $3, NULL, NULL);}
		| TK_IDENTIFICADOR '['condicao']'{$$ = astCreate(IKS_AST_VETOR_INDEXADO,$1, $3, NULL, NULL, NULL);}
		| chamada_funcao		{$$ = $1;}
		;
		

saida:     	TK_IDENTIFICADOR		{$$ = astCreate(IKS_AST_IDENTIFICADOR, $1, NULL, NULL, NULL, NULL);}
		|TK_LIT_STRING			{$$ = astCreate(IKS_AST_LITERAL, $1, NULL, NULL, NULL, NULL);}
		| '(' saida')'			{$$=$2;}
        	| '*' saida			{$$=$2;}
		| saida '+' saida		{$$ = astCreate(IKS_AST_ARIM_SOMA,NULL, $1, $3, NULL, NULL);}
		| saida '*' saida		{$$ = astCreate(IKS_AST_ARIM_MULTIPLICACAO,NULL, $1, $3, NULL, NULL);}
		| saida '/' saida		{$$ = astCreate(IKS_AST_ARIM_DIVISAO,NULL, $1, $3, NULL, NULL);}
		| saida '-' saida		{$$ = astCreate(IKS_AST_ARIM_SUBTRACAO,NULL, $1, $3, NULL, NULL);}
		| '-' saida			{$$ = astCreate(IKS_AST_ARIM_INVERSAO,NULL, $2, NULL, NULL, NULL);}
		| saida TK_OC_LE saida		{$$ = astCreate(IKS_AST_LOGICO_COMP_LE,NULL, $1, $3, NULL, NULL);}
		| saida TK_OC_GE saida		{$$ = astCreate(IKS_AST_LOGICO_COMP_GE,NULL, $1, $3, NULL, NULL);}
		| saida TK_OC_EQ saida		{$$ = astCreate(IKS_AST_LOGICO_COMP_IGUAL,NULL, $1, $3, NULL, NULL);}
		| saida TK_OC_NE saida		{$$ = astCreate(IKS_AST_LOGICO_COMP_DIF,NULL, $1, $3, NULL, NULL);}
		| saida '>' saida		{$$ = astCreate(IKS_AST_LOGICO_COMP_G,NULL, $1, $3, NULL, NULL);}
		| saida '<' saida		{$$ = astCreate(IKS_AST_LOGICO_COMP_L,NULL, $1, $3, NULL, NULL);}
		| saida TK_OC_AND saida		{$$ = astCreate(IKS_AST_LOGICO_E,NULL, $1, $3, NULL, NULL);}
		| saida TK_OC_OR saida		{$$ = astCreate(IKS_AST_LOGICO_OU,NULL, $1, $3, NULL, NULL);}
		| TK_IDENTIFICADOR '['saida ']'	{$$ = astCreate(IKS_AST_VETOR_INDEXADO,$1, $3, NULL, NULL, NULL);}
		| chamada_funcao		{$$ = $1;}
		;	 

%%


