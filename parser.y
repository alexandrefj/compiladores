%{
#include <stdio.h>
#include<stdlib.h>
%}

//%union {int a_number;}
//%type <a_number> type
//%start type
/* Declaração dos tokens da gramática da Linguagem K */

//#define TK_PR_INT         256   /* int       */
//#define TK_PR_FLOAT       257   /* float     */
//#define TK_PR_BOOL        258   /* bool      */
//#define TK_PR_CHAR        259   /* char      */
//#define TK_PR_STRING      260   /* string    */
//#define TK_PR_IF          261   /* if        */
//#define TK_PR_THEN        262   /* then      */
//#define TK_PR_ELSE        263   /* else      */
//#define TK_PR_WHILE       264   /* while     */
//#define TK_PR_DO          265   /* do        */
//#define TK_PR_INPUT       266   /* input     */
//#define TK_PR_OUTPUT      267   /* output    */
//#define TK_PR_RETURN      268   /* return    */
/* Operadores Compostos (OC) */

//#define TK_OC_LE    270   /* <=        */
//#define TK_OC_GE    271   /* >=        */
//#define TK_OC_EQ    272   /* ==        */
//#define TK_OC_NE    273   /* !=        */
//#define TK_OC_AND   274   /* &&        */
//#define TK_OC_OR    275   /* ||        */

/* Literais (LIT) */
//#define TK_LIT_INT        281
//#define TK_LIT_FLOAT      282
//#define TK_LIT_FALSE      283
//#define TK_LIT_TRUE       284
//#define TK_LIT_CHAR       285
//#define TK_LIT_STRING     286

/* Indentificador */
//#define TK_IDENTIFICADOR  290

/* Erro */
//#define TOKEN_ERRO        291


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

%%
 /* Regras (e ações) da gramática da Linguagem K */

//Um programa na linguagem IKS é composto por um conjunto opcional de declarações de variáveis globais e um
//conjunto opcional de funções, que podem aparecer intercaladamente e em qualquer ordem.

program 		:global_var_decl program
			|function program
			|
			;

function		:type ':' TK_IDENTIFICADOR '('param_list')' local_var_decl '{'block'}';


local_var_decl		:type ':' TK_IDENTIFICADOR';'
			|type ':' TK_IDENTIFICADOR';' local_var_decl
			|
			;

block			: simple_command block
			| control_flow_command block
			|
			;



global_var_decl		: type ':' TK_IDENTIFICADOR';'
			| type TK_IDENTIFICADOR '['TK_LIT_INT']'';'
			;


simple_command		:TK_PR_INPUT TK_IDENTIFICADOR ';' simple_command
			|TK_IDENTIFICADOR '=' exp';' simple_command		//represents attribution
			|TK_IDENTIFICADOR'['exp']' '=' exp';' simple_command	//either
			|TK_PR_OUTPUT output ';' simple_command
			|TK_PR_RETURN return ';' simple_command
			|
			;

control_flow_command	:TK_PR_IF '('exp')'TK_PR_THEN simple_command
			|TK_PR_IF '('exp')'TK_PR_THEN simple_command TK_PR_ELSE simple_command
			|TK_PR_WHILE '('exp')'TK_PR_DO simple_command	
			|TK_PR_DO simple_command TK_PR_WHILE'('exp')'
			;

return			: exp
			| TK_IDENTIFICADOR;


param_list		:type ':'TK_IDENTIFICADOR
			|type ':'TK_IDENTIFICADOR ',' param_list
			|
			;

exp			: constant
			| TK_IDENTIFICADOR '=' TK_IDENTIFICADOR '('param_list')'
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
			| '!' exp
        		;

constant		: TK_LIT_INT
			| TK_LIT_FLOAT
			| TK_LIT_TRUE
			| TK_LIT_FALSE
			| TK_LIT_CHAR
			| TK_LIT_STRING
			;

output			:TK_IDENTIFICADOR
			|exp
			|TK_IDENTIFICADOR ',' output
			|exp ',' output
			;
 
type			:TK_PR_INT
			|TK_PR_FLOAT
			|TK_PR_BOOL
			|TK_PR_STRING
			|TK_PR_CHAR
			;



%%



