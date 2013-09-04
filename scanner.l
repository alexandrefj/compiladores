%{

#include "string.h"
#include "stdlib.h"
#include "parser.h"
#include "main.h"

int numerodelinhas = 1;

int getLineNumber(void){ return numerodelinhas;}
void initMe(void) { dict_init(); }

%}

INTEGER		[0-9]
HEXA		[a-fA-F]
CHAR		[a-zA-Z_]
SPECIAL		[,;:(){}\[\]{}\+\-\*<>=!&$\/]
%x comment

%%



"int"      return TK_PR_INT;
"float"    return TK_PR_FLOAT; 
"bool"     return TK_PR_BOOL; 
"char"     return TK_PR_CHAR; 
"string"   return TK_PR_STRING; 
"if"       return TK_PR_IF; 
"then"     return TK_PR_THEN; 
"else"     return TK_PR_ELSE; 
"while"    return TK_PR_WHILE; 
"do"       return TK_PR_DO; 
"input"    return TK_PR_INPUT; 
"output"   return TK_PR_OUTPUT; 
"return"   return TK_PR_RETURN; 
"true"     {yylval.symbol = dict_insert(yytext,IKS_SIMBOLO_LITERAL_BOOL); return TK_LIT_TRUE;}
"false"    {yylval.symbol = dict_insert(yytext,IKS_SIMBOLO_LITERAL_BOOL); return TK_LIT_FALSE;}


{CHAR}({CHAR}|{INTEGER})*      	{yylval.symbol = dict_insert(yytext,TK_IDENTIFICADOR); return TK_IDENTIFICADOR;}

[0-9]+                	        {yylval.symbol = dict_insert(yytext,IKS_SIMBOLO_LITERAL_INT); return TK_LIT_INT;}

'(\\.|[^\\'])+'                 {yylval.symbol = dict_insert(yytext,IKS_SIMBOLO_LITERAL_CHAR); return TK_LIT_CHAR;}

\"(\\.|[^\\"])*\"              	{yylval.symbol = dict_insert(yytext,IKS_SIMBOLO_LITERAL_STRING); return TK_LIT_STRING;}                         
    
[0-9]*\.[0-9]+	                {yylval.symbol = dict_insert(yytext,IKS_SIMBOLO_LITERAL_FLOAT); return TK_LIT_FLOAT;}

\s     
                 

{SPECIAL}  return yytext[0];


"<="						return TK_OC_LE;
">="						return TK_OC_GE;
"=="						return TK_OC_EQ;
"!="						return TK_OC_NE;
"&&"						return TK_OC_AND;
"||"						return TK_OC_OR;
\n { ++numerodelinhas;}


[ \t\v\f]						/* Ignorar caracteres inuteis */
\/\/.*							/* Ignorar comentarios */
"/*"         						BEGIN comment;	
<comment>"\n"						++numerodelinhas;
<comment>.						
<comment>"*/"						BEGIN(INITIAL);

. {return TOKEN_ERRO; exit(IKS_SYNTAX_ERRO);}

					
%%
