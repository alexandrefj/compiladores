%{
#include "tokens.h"
#include "comp_dict.h"
#include "string.h"
#include "stdlib.h"
int numerodelinhas = 1;
char destino[20];


int getLineNumber(void){ return numerodelinhas;}

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

{CHAR}({CHAR}|{INTEGER})*       { sprintf(destino, "%d",numerodelinhas); dict_insert(yytext, destino); return TK_IDENTIFICADOR; }
-?[0-9]+                        { sprintf(destino, "%d",numerodelinhas); dict_insert(yytext, destino); return TK_LIT_INT; }
'(\\.|[^\\'])+'                 { sprintf(destino, "%d",numerodelinhas); dict_insert(yytext, destino); return TK_LIT_CHAR; }
\"(\\.|[^\\"])*\"               { sprintf(destino, "%d",numerodelinhas); dict_insert(yytext, destino); return TK_LIT_STRING; }
"true"                          { sprintf(destino, "%d",numerodelinhas); dict_insert(yytext, destino); return TK_LIT_TRUE; }
"false"                         { sprintf(destino, "%d",numerodelinhas); dict_insert(yytext, destino); return TK_LIT_FALSE; }     
-?[0-9]*\.[0-9]+                { sprintf(destino, "%d",numerodelinhas); dict_insert(yytext, destino); return TK_LIT_FLOAT; }

" "                                

. { return TOKEN_ERRO; }

{SPECIAL}		        return yytext[0];


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
					
%%
