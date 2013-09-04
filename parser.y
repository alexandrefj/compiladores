%{
#include <stdio.h>
#include<stdlib.h>
#include "comp_dict.h"
%}

%union
{
struct nome_interno *symbol;
int type;
}

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


%type<type> constant

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

%nonassoc TK_PR_THEN
%nonassoc TK_PR_ELSE

%%

/*******************************************************************************************
----------------------REGRAS DA LINGUAGEM IKS---------------------------------------------**
*******************************************************************************************/

program 		:global_var_decl program
			|function program
			|
			;

function		:type ':' TK_IDENTIFICADOR '('param_list')' local_var_decl '{' block'}' ;


local_var_decl		:type ':' TK_IDENTIFICADOR';'
			|type ':' TK_IDENTIFICADOR';' local_var_decl
			|
			;

block			: simple_command block
			| control_flow_command block
			| '{'simple_command block'}'
			|
			;

flow_block		: simple_command_function
			| '{' simple_command flow_block '}' ';'
			|
			;

simple_command_function: TK_PR_INPUT TK_IDENTIFICADOR ';'
			|TK_IDENTIFICADOR '=' exp';'	
			|TK_IDENTIFICADOR'['exp']' '=' exp';' 	
			|TK_PR_OUTPUT output ';' 
			|TK_PR_RETURN return ';'
			|TK_IDENTIFICADOR '=' exp	
			|TK_IDENTIFICADOR'['exp']' '=' exp
			|TK_PR_OUTPUT output 
			|TK_PR_RETURN return
			|';'
			;


global_var_decl		: type ':' TK_IDENTIFICADOR';'		
			| type ':' TK_IDENTIFICADOR '['TK_LIT_INT']'';'
			;


simple_command		:TK_PR_INPUT TK_IDENTIFICADOR ';'
			|TK_IDENTIFICADOR '=' exp';'	
			|TK_IDENTIFICADOR'['exp']' '=' exp';' 	
			|TK_PR_OUTPUT output ';' 
			|TK_PR_RETURN return ';'
			|';'
			|
			;

control_flow_command	:TK_PR_IF '('exp')'TK_PR_THEN flow_block 
			|TK_PR_IF '('exp')'TK_PR_THEN flow_block TK_PR_ELSE flow_block 
			|TK_PR_WHILE '('exp')'TK_PR_DO flow_block 
			|TK_PR_DO flow_block TK_PR_WHILE'('exp')'
			;

return			: exp
			| TK_IDENTIFICADOR;


param_list		:type ':'TK_IDENTIFICADOR param_list
			|',' type ':'TK_IDENTIFICADOR param_list
			|
			;

call_param_list		: constant call_param_list
			| TK_IDENTIFICADOR'['exp']' call_param_list 
			| ',' constant call_param_list
			| ',' TK_IDENTIFICADOR'['exp']' call_param_list
			|
			;

exp			: constant
			| TK_IDENTIFICADOR
			| '(' exp ')'
        		| '&'exp
        		| '*'exp
			| exp '*' exp
			| exp '/' exp
			| exp '+' exp	
			| exp '-' exp	
			| exp TK_OC_LE exp
			| exp TK_OC_GE exp
			| exp TK_OC_EQ exp
			| exp TK_OC_NE exp
			| exp '>' exp
			| exp '<' exp
			| exp TK_OC_AND exp
			| exp TK_OC_OR exp
			| TK_IDENTIFICADOR '[' exp ']'
			| TK_IDENTIFICADOR '('call_param_list')'
        		;

/* 	Tentei definir os tipos, porém não
	sei ao certo se foi isso que foi 
	pedido na especificação		*/


constant		: TK_LIT_INT		{$$ = 1;}
			| '-'TK_LIT_INT 	{$$ = 1;}
			| TK_LIT_FLOAT		{$$ = 2;}
			| '-'TK_LIT_FLOAT	{$$ = 2;}
			| TK_LIT_STRING		{$$ = 3;}
			| TK_LIT_CHAR		{$$ = 4;}
			| TK_LIT_TRUE		{$$ = 5;}
			| TK_LIT_FALSE		{$$ = 5;}
			;

output			:exp
			|exp ',' output
			|
			;
 
type			:TK_PR_INT
			|TK_PR_FLOAT
			|TK_PR_BOOL
			|TK_PR_STRING
			|TK_PR_CHAR
			;

%%


