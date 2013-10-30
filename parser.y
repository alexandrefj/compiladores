%{
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "semantic.h"
%}
%union
{
struct nome_interno *symbol;
struct astreenode *ast;
}
%type<ast> chamada_com_param
%type<ast> nome_variavel
%type<ast> vetor
%type<ast> vetor_cham
%type<ast> vetor_cond
%type<ast> inicio
%type<ast> programa
%type<ast> comando_condicao
%type<ast> comando_composto
%type<ast> comando_simples
%type<ast> comando
%type<ast> expressao
%type<ast> chamada_recursao
%type<ast> literal
%type<ast> colchetes
%type<ast> condicao
%type<ast> bloco
%type<ast> bloco_c
%type<ast> exp2
%type<symbol> exp1
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
%left TK_OC_OR 
%right TK_OC_AND
%left '-' '+' 
%right ','
%right '!'
%left '*' '/'
%left ')'
%left ']'
%start inicio
%nonassoc TK_PR_THEN
%nonassoc TK_PR_ELSE
%%			/******************************************************************************************************************************
			**-----------------------------------------------REGRAS DA LINGUAGEM IKS-----------------------------------------------------**
			******************************************************************************************************************************/
			/*-----------------------------------------------ANALISE SINTATICA-----------------------------------------------------------*/

inicio:			{init_lists();} programa	{root = astCreate(IKS_AST_PROGRAMA, NULL, $2, NULL, NULL, NULL);stack_push(stack_pointer,$$);ILOC_GEN(code);/*exit(IKS_SUCCESS);*/;};

programa:	  	tipo ':' TK_IDENTIFICADOR 
			{
			stack_pointer = stack_init();
			func_id++;
			local_var = NULL;
			func_type = type;
			function_list=FunctionListInsert(function_list,$3,type,func_id);
			}
			'('parametros_funcao')'  declaracao_var_locais 
			{
			aux2 = list_insert(aux2,0,0,"end",0);
			VarDeslocGen(global_code,GLOBAL,aux2);VarDeslocGen(local_var,LOCAL,NULL);
			}
			'{'comando'}' 
			{
			if(stack_pointer!= NULL){
				stack_pointer=invert_stack(stack_pointer);
				StackPopCommands(stack_pointer, global_var,global_vet,local_var,function_list,param_list);	
			}
			}
			programa 
			{$$ = astCreate(IKS_AST_FUNCAO, $3, $11, $14, NULL, NULL);stack_push(stack_pointer,$$);}	
		   	|declaracao_var_globais programa		{$$=$2;}
		   	|						{$$=NULL;}				
		   	;

comando: 		comando_composto 
			|comando_simples
			|bloco					{$$=astCreate(IKS_AST_BLOCO,NULL,$1,NULL, NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);}
			|bloco ';' comando			{$$=astCreate(IKS_AST_BLOCO,NULL,$1,$3, NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);}
			|comando_condicao
			|					{$$=NULL;}
			;

comando_simples:	TK_PR_INPUT exp2	 		{$$ = astCreate(IKS_AST_INPUT, NULL, $2,NULL, NULL, NULL); 	 stack_pointer=stack_push(stack_pointer,$$);}
			|nome_variavel '=' expressao		{$$ = astCreate(IKS_AST_ATRIBUICAO,NULL,$1,$3,NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);
								code=CodeGenerate_store($$,code);}
			|vetor '=' expressao			{$$ = astCreate(IKS_AST_ATRIBUICAO,NULL,$1,$3,NULL,NULL);stack_pointer=stack_push(stack_pointer,$$);
								code=CodeGenerate_store($$,code);}
			|TK_PR_RETURN expressao 		{$$ = astCreate(IKS_AST_RETURN,NULL,$2,NULL, NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);
								code=CodeGenerate_nop($$,code);}
			|nome_variavel '(' chamada_recursao ')' {$$ = astCreate(IKS_AST_CHAMADA_DE_FUNCAO,NULL,$1,$3,NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);}
			|TK_PR_OUTPUT chamada_com_param		{$$ = astCreate(IKS_AST_OUTPUT,NULL,$2,NULL, NULL, NULL);	 stack_pointer=stack_push(stack_pointer,$$);}
			;

comando_composto:	TK_PR_INPUT exp2 ';' 	comando {$$ = astCreate(IKS_AST_INPUT, NULL, $2, $4, NULL, NULL); stack_pointer=stack_push(stack_pointer,$$);}
			|nome_variavel '=' expressao';'  comando{$$ = astCreate(IKS_AST_ATRIBUICAO,NULL,$1,$3,$5, NULL); stack_pointer=stack_push(stack_pointer,$$);
								code=CodeGenerate_store($$,code);}
			|vetor '=' expressao';'  comando 	{$$ = astCreate(IKS_AST_ATRIBUICAO,NULL,$1,$3,$5,NULL);stack_pointer=stack_push(stack_pointer,$$);
								code=CodeGenerate_store($$,code);}
			|TK_PR_RETURN expressao ';' comando	{$$ = astCreate(IKS_AST_RETURN,NULL,$2,$4, NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);
								code=CodeGenerate_nop($$,code);}
			|nome_variavel '(' chamada_recursao ')' ';' comando	{$$ = astCreate(IKS_AST_CHAMADA_DE_FUNCAO,NULL,$1,$3,$6, NULL); stack_pointer=stack_push(stack_pointer,$$);}
			|TK_PR_OUTPUT chamada_com_param ';' comando		{$$ = astCreate(IKS_AST_OUTPUT,NULL,$2,$4, NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);}
			|';' comando						{$$= $2;};

bloco:			'{'comando'}' {$$ = $2;
					code=CodeGenerate_nop($$,code);} ;

bloco_c:		'{'comando'}' {$$=astCreate(IKS_AST_BLOCO,NULL,$2,NULL, NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);
					code=CodeGenerate_nop($$,code);};

comando_condicao: 	TK_PR_IF '('condicao')'TK_PR_THEN bloco_c comando			
			{$$ = astCreate(IKS_AST_IF_ELSE, NULL, $3, $6, $7, NULL);stack_pointer=stack_push(stack_pointer,$$);code = CodeGenerate_cbr($$,code);}
			|TK_PR_IF '('condicao')'TK_PR_THEN comando_simples ';' comando			
			{$$ = astCreate(IKS_AST_IF_ELSE, NULL, $3, $6, $8, NULL);stack_pointer=stack_push(stack_pointer,$$);code = CodeGenerate_cbr($$,code);}
			|TK_PR_IF '('condicao')'TK_PR_THEN comando_simples TK_PR_ELSE comando_simples ';' comando
			{$$ = astCreate(IKS_AST_IF_ELSE, NULL, $3, $6, $8, NULL);stack_pointer=stack_push(stack_pointer,$$);code = CodeGenerate_cbr($$,code);}
			|TK_PR_IF '('condicao')'TK_PR_THEN bloco_c TK_PR_ELSE bloco_c comando 			
			{$$ = astCreate(IKS_AST_IF_ELSE, NULL, $3, $6, $8, $9);stack_pointer=stack_push(stack_pointer,$$);code = CodeGenerate_cbr($$,code);}
			|TK_PR_WHILE '('condicao')' TK_PR_DO bloco_c comando				
			{$$ = astCreate(IKS_AST_WHILE_DO, NULL, $3, $6, $7, NULL);stack_pointer=stack_push(stack_pointer,$$);}
			|TK_PR_WHILE '('condicao')' TK_PR_DO comando_simples ';' comando		
			{$$ = astCreate(IKS_AST_WHILE_DO, NULL, $3, $6, $8, NULL);stack_pointer=stack_push(stack_pointer,$$);}
			|TK_PR_DO bloco_c TK_PR_WHILE'('condicao')' comando				
			{$$ = astCreate(IKS_AST_DO_WHILE, NULL, $2, $5, $7, NULL);stack_pointer=stack_push(stack_pointer,$$);}
			|TK_PR_DO comando_simples TK_PR_WHILE'('condicao')' comando 			
			{$$ = astCreate(IKS_AST_DO_WHILE, NULL, $2, $5, $7, NULL);stack_pointer=stack_push(stack_pointer,$$);};

nome_variavel:		TK_IDENTIFICADOR		{$$ = astCreate(IKS_AST_IDENTIFICADOR, $1, NULL, NULL, NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);
							code=CodeGenerate_loadAI($$,code);};
vetor:			nome_variavel '['expressao']' colchetes  {$$ = astCreate(IKS_AST_VETOR_INDEXADO, NULL, $1, $3, $5, NULL);stack_pointer=stack_push(stack_pointer,$$);
								code=CodeGenerate_loadAI($$,code);};
vetor_cham:		nome_variavel '['expressao']' colchetes ',' chamada_com_param	 {$$ = astCreate(IKS_AST_VETOR_INDEXADO, NULL, $1, $3, $5, $7);stack_pointer=stack_push(stack_pointer,$$);};
vetor_cond:		nome_variavel '['condicao ']' colchetes  {$$ = astCreate(IKS_AST_VETOR_INDEXADO, NULL, $1, $3, $5, NULL);stack_pointer=stack_push(stack_pointer,$$);};
colchetes:		 '['expressao']' colchetes 		{$$ = astCreate(IKS_AST_VETOR_INDEXADO, NULL, $2, $4, NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);
								code=CodeGenerate_nop($$,code);code = code->next;}
			| 					{$$ = NULL;};

chamada_recursao: 	chamada_com_param													
			{$$=$1;}
			|													
			{$$=NULL;};

chamada_com_param:	exp2																
			{$$ =$1;}
			| nome_variavel '(' chamada_recursao ')'				
			{$$ = astCreate(IKS_AST_CHAMADA_DE_FUNCAO, NULL, $1, $3, NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);}
			|vetor	{$$ = $1;code=CodeGenerate_nop($$,code);}	
			| exp2 '+'  exp2						  
			{$$ = astCreate(IKS_AST_ARIM_SOMA,NULL,$1, $3,NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);code=CodeGenerate_add($$,code); }
			| exp2 '-' exp2							  
			{$$ = astCreate(IKS_AST_ARIM_SUBTRACAO,NULL,$1, $3,NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);code=CodeGenerate_sub($$,code);}
			| exp2 '*' exp2							  
			{$$ = astCreate(IKS_AST_ARIM_MULTIPLICACAO,NULL,$1, $3,NULL, NULL); stack_pointer=stack_push(stack_pointer,$$);code=CodeGenerate_mult($$,code);}
			| exp2 '/' exp2							  
			{$$ = astCreate(IKS_AST_ARIM_DIVISAO,NULL,$1, $3,NULL, NULL); stack_pointer=stack_push(stack_pointer,$$);code=CodeGenerate_div($$,code);}	
			| exp1','chamada_com_param						
			{$$ = astCreate(IKS_AST_LITERAL, $1, $3, NULL, NULL, NULL);stack_pointer= stack_push(stack_pointer,$$);}
			| nome_variavel '(' chamada_recursao ')' ',' chamada_com_param		
			{$$ = astCreate(IKS_AST_CHAMADA_DE_FUNCAO, NULL, $1, $3, $6, NULL);stack_pointer=stack_push(stack_pointer,$$);}
			| vetor_cham {$$=$1;}
			| exp2 '+'  exp2 ',' chamada_com_param					 
			{$$ = astCreate(IKS_AST_ARIM_SOMA,NULL,$1, $3,$5, NULL);stack_pointer=stack_push(stack_pointer,$$);code=CodeGenerate_add($$,code);}
			| exp2 '-' exp2 ',' chamada_com_param					 
			{$$ = astCreate(IKS_AST_ARIM_SUBTRACAO,NULL,$1, $3,$5, NULL);stack_pointer=stack_push(stack_pointer,$$);code=CodeGenerate_sub($$,code);}
			| exp2 '*' exp2 ',' chamada_com_param					 
			{$$ = astCreate(IKS_AST_ARIM_MULTIPLICACAO,NULL,$1, $3,$5, NULL);stack_pointer= stack_push(stack_pointer,$$);code=CodeGenerate_mult($$,code);}
			| exp2 '/' exp2 ',' chamada_com_param					 
			{$$ = astCreate(IKS_AST_ARIM_DIVISAO,NULL,$1, $3,$5,NULL);stack_pointer=stack_push(stack_pointer,$$);code=CodeGenerate_div($$,code);};		

exp1:		 	TK_LIT_INT		{$$ = $1;}		
			| TK_LIT_FLOAT		{$$ = $1;}
			| TK_LIT_STRING		{$$ = $1;}	
			| TK_LIT_CHAR		{$$ = $1;}
			| TK_LIT_TRUE		{$$ = $1;}	
			| TK_LIT_FALSE		{$$ = $1;}
			| TK_IDENTIFICADOR	{$$ = $1;}
			;

exp2:			 TK_LIT_INT		{$$ = astCreate(IKS_AST_LITERAL, $1, NULL, NULL, NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);}		
			| TK_LIT_FLOAT		{$$ = astCreate(IKS_AST_LITERAL, $1, NULL, NULL, NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);}
			| TK_LIT_STRING		{$$ = astCreate(IKS_AST_LITERAL, $1, NULL, NULL, NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);}	
			| TK_LIT_CHAR		{$$ = astCreate(IKS_AST_LITERAL, $1, NULL, NULL, NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);}
			| TK_LIT_TRUE		{$$ = astCreate(IKS_AST_LITERAL, $1, NULL, NULL, NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);}	
			| TK_LIT_FALSE		{$$ = astCreate(IKS_AST_LITERAL, $1, NULL, NULL, NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);}
			| TK_IDENTIFICADOR	{$$ = astCreate(IKS_AST_IDENTIFICADOR, $1, NULL, NULL, NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);}
			;


expressao:		TK_IDENTIFICADOR				{$$ = astCreate(IKS_AST_IDENTIFICADOR, $1, NULL, NULL, NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);
									code=CodeGenerate_loadAI($$,code);}
			|literal 					{$$ = $1;}
			| '(' expressao')'				{$$ = $2;}
        		| '*' expressao					{$$ = $2;}
			| '!' expressao					{$$=astCreate(IKS_AST_LOGICO_COMP_NEGACAO,NULL,$2,NULL,NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);}
			| expressao '+' expressao			{$$ = astCreate(IKS_AST_ARIM_SOMA,NULL, $1, $3, NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);
									code=CodeGenerate_add($$,code);}
			| expressao '*' expressao			{$$ = astCreate(IKS_AST_ARIM_MULTIPLICACAO,NULL, $1, $3, NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);
									code=CodeGenerate_mult($$,code);}
			| expressao '/' expressao			{$$ = astCreate(IKS_AST_ARIM_DIVISAO,NULL, $1, $3, NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);
									code=CodeGenerate_div($$,code);}
			| expressao '-' expressao			{$$ = astCreate(IKS_AST_ARIM_SUBTRACAO,NULL, $1, $3, NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);
									code=CodeGenerate_sub($$,code);}
			| '-' expressao					{$$ = astCreate(IKS_AST_ARIM_INVERSAO,NULL, $2, NULL, NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);}
			| expressao TK_OC_LE expressao			{$$ = astCreate(IKS_AST_LOGICO_COMP_LE,NULL, $1, $3, NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);
									code=CodeGenerate_cmp_LE($$,code);}
			| expressao TK_OC_GE expressao			{$$ = astCreate(IKS_AST_LOGICO_COMP_GE,NULL, $1, $3, NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);
									code=CodeGenerate_cmp_GE($$,code);}
			| expressao TK_OC_EQ expressao			{$$ = astCreate(IKS_AST_LOGICO_COMP_IGUAL,NULL, $1, $3, NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);
									code=CodeGenerate_cmp_EQ($$,code);}
			| expressao TK_OC_NE expressao			{$$ = astCreate(IKS_AST_LOGICO_COMP_DIF,NULL, $1, $3, NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);
									code=CodeGenerate_cmp_NE($$,code);}
			| expressao '>' expressao			{$$ = astCreate(IKS_AST_LOGICO_COMP_G,NULL, $1, $3, NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);
									code=CodeGenerate_cmp_GT($$,code);}
			| expressao '<' expressao			{$$ = astCreate(IKS_AST_LOGICO_COMP_L,NULL, $1, $3, NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);
									code=CodeGenerate_cmp_LT($$,code);}
			| expressao TK_OC_AND expressao			{$$ = astCreate(IKS_AST_LOGICO_E,NULL, $1, $3, NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);
									code=CodeGenerate_and($$,code);}
			| expressao TK_OC_OR expressao			{$$ = astCreate(IKS_AST_LOGICO_OU,NULL, $1, $3, NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);
									code=CodeGenerate_or($$,code);}
			| vetor 					{$$ = $1;}
			| nome_variavel '(' chamada_recursao ')' 	{$$ = astCreate(IKS_AST_CHAMADA_DE_FUNCAO, NULL, $1, $3, NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);};

condicao:		TK_IDENTIFICADOR				{$$ = astCreate(IKS_AST_IDENTIFICADOR, $1, NULL, NULL, NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);
									code=CodeGenerate_loadAI($$,code);}
			|literal					{$$=$1;}
			| '(' condicao')'				{$$=$2;}
        		| '*' condicao					{$$=$2;}
			| '!' condicao					{$$ = astCreate(IKS_AST_LOGICO_COMP_NEGACAO,NULL, $2, NULL, NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);}
			| condicao '+' condicao				{$$ = astCreate(IKS_AST_ARIM_SOMA,NULL, $1, $3, NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);
									code=CodeGenerate_add($$,code);}
			| condicao '*' condicao				{$$ = astCreate(IKS_AST_ARIM_MULTIPLICACAO,NULL, $1, $3, NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);
									code=CodeGenerate_mult($$,code);}
			| condicao '/' condicao				{$$ = astCreate(IKS_AST_ARIM_DIVISAO,NULL, $1, $3, NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);
									code=CodeGenerate_div($$,code);}
			| condicao '-' condicao				{$$ = astCreate(IKS_AST_ARIM_SUBTRACAO,NULL, $1, $3, NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);
									code=CodeGenerate_sub($$,code);}
			| '-' condicao					{$$ = astCreate(IKS_AST_ARIM_INVERSAO,NULL, $2, NULL, NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);}
			| condicao TK_OC_LE condicao			{$$ = astCreate(IKS_AST_LOGICO_COMP_LE,NULL, $1, $3, NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);
									code=CodeGenerate_cmp_LE($$,code);}
			| condicao TK_OC_GE condicao			{$$ = astCreate(IKS_AST_LOGICO_COMP_GE,NULL, $1, $3, NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);
									code=CodeGenerate_cmp_GE($$,code);}
			| condicao TK_OC_EQ condicao			{$$ = astCreate(IKS_AST_LOGICO_COMP_IGUAL,NULL, $1, $3, NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);
									code=CodeGenerate_cmp_EQ($$,code);}
			| condicao TK_OC_NE condicao			{$$ = astCreate(IKS_AST_LOGICO_COMP_DIF,NULL, $1, $3, NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);
									code=CodeGenerate_cmp_NE($$,code);}
			| condicao '>' condicao				{$$ = astCreate(IKS_AST_LOGICO_COMP_G,NULL, $1, $3, NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);
									code=CodeGenerate_cmp_GT($$,code);}
			| condicao '<' condicao				{$$ = astCreate(IKS_AST_LOGICO_COMP_L,NULL, $1, $3, NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);
									code=CodeGenerate_cmp_LT($$,code);}
			| condicao TK_OC_AND condicao			{$$ = astCreate(IKS_AST_LOGICO_E,NULL, $1, $3, NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);
									code=CodeGenerate_and($$,code);}
			| condicao TK_OC_OR condicao			{$$ = astCreate(IKS_AST_LOGICO_OU,NULL, $1, $3, NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);
									code=CodeGenerate_or($$,code);}
			| vetor_cond 					{$$ = $1;}
			| nome_variavel '(' chamada_recursao ')' 	{$$ = astCreate(IKS_AST_CHAMADA_DE_FUNCAO, NULL, $1, $3, NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);};

literal:         	TK_LIT_INT					{$$ = astCreate(IKS_AST_LITERAL, $1, NULL, NULL, NULL, NULL);stack_pointer=stack_push(stack_pointer,$$); 
									code=CodeGenerate_loadI($$,code);}		
			| TK_LIT_FLOAT					{$$ = astCreate(IKS_AST_LITERAL, $1, NULL, NULL, NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);
									code=CodeGenerate_loadI($$,code);}
			| TK_LIT_STRING					{$$ = astCreate(IKS_AST_LITERAL, $1, NULL, NULL, NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);}	
			| TK_LIT_CHAR					{$$ = astCreate(IKS_AST_LITERAL, $1, NULL, NULL, NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);}
			| TK_LIT_TRUE					{$$ = astCreate(IKS_AST_LITERAL, $1, NULL, NULL, NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);}	
			| TK_LIT_FALSE					{$$ = astCreate(IKS_AST_LITERAL, $1, NULL, NULL, NULL, NULL);stack_pointer=stack_push(stack_pointer,$$);};

parametros_funcao: 	parametros_funcao_c_param
			|;

parametros_funcao_c_param:
			tipo ':' TK_IDENTIFICADOR  
			{
			local_var=LocalVarListInsert(local_var,$3,type,0,function_list); param_list =list_insert(param_list,type,func_id,$3->text,0);
			}
			| tipo ':'TK_IDENTIFICADOR 
			{
			local_var=LocalVarListInsert(local_var,$3,type,0,function_list); param_list =list_insert(param_list,type,func_id,$3->text,0);
			}
			',' parametros_funcao_c_param;

declaracao_var_locais:  tipo ':' TK_IDENTIFICADOR 
			{
			local_var=LocalVarListInsert(local_var,$3,type,0,function_list);
			}	
			';' declaracao_var_locais			
			| ;

declaracao_var_globais: tipo ':' TK_IDENTIFICADOR';'					
			{
			global_var=GlobalVarListInsert(global_var,$3,GLOBAL_VAR_DEC_IDENTIFIER_CONTROL,type,0);
			global_code = list_insert(global_code,type,0,$3->text,1);
			}


			|tipo ':' TK_IDENTIFICADOR '['TK_LIT_INT']'
			{
			aux2 = list_insert(aux2,type,0, $3->text, atoi($5->text));
			array_el = atoi($5->text);
			} colchete_dec';'
			{
			global_vet=GlobalVarListInsert(global_vet,$3,GLOBAL_VET_DEC_IDENTIFIER_CONTROL,type,atoi($5->text));
			global_code = list_insert(global_code,type,0,$3->text,array_el);
			global_code->dim = list_copy(global_code->dim,aux2);
			};

colchete_dec:		 '['TK_LIT_INT']' colchete_dec 	{array_el = array_el*atoi($2->text);
							aux2 = list_insert(aux2,type,0,"nop", atoi($2->text));
							}
			| 				
			;

tipo:        		TK_PR_INT	{type = 1;}
			|TK_PR_FLOAT	{type = 2;}	
			|TK_PR_BOOL	{type = 5;}		
			|TK_PR_STRING	{type = 4;}		
			|TK_PR_CHAR	{type = 3;};
%%
init_lists(){
	global_code = list_init();
	code = TAC_init();
	stack_pointer=stack_init();
	global_var = list_init();
	global_vet = list_init();
	local_var = list_init();
	function_list = list_init();
	param_list = list_init();
}


