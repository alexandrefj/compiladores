%{
#include "tokens.h"
#include "string.h"
#include "stdlib.h"
#include "main.h"
int numerodelinhas = 1;
DICT* dictionary;
void init_me(void);
int getLineNumber(void){ return numerodelinhas;}
DICT* get_dict(void){return dictionary;}
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

{CHAR}({CHAR}|{INTEGER})*        {if(dictionary == NULL) dictionary = dict_insert(dictionary,numerodelinhas,yytext,IKS_SIMBOLO_INDEFINIDO);
				 else dict_insert(dictionary,numerodelinhas,yytext,IKS_SIMBOLO_INDEFINIDO); return TK_IDENTIFICADOR;}

-?[0-9]+                         {if(dictionary == NULL) dictionary = dict_insert(dictionary,numerodelinhas,yytext,IKS_SIMBOLO_LITERAL_INT);
				 else dict_insert(dictionary,numerodelinhas,yytext,IKS_SIMBOLO_LITERAL_INT); return TK_LIT_INT;}

'(\\.|[^\\'])+'                  {if(dictionary == NULL) dictionary = dict_insert(dictionary,numerodelinhas,yytext,IKS_SIMBOLO_LITERAL_CHAR);
				 else dict_insert(dictionary,numerodelinhas,yytext,IKS_SIMBOLO_LITERAL_CHAR); return TK_LIT_CHAR;}

\"(\\.|[^\\"])*\"                {if(dictionary == NULL) dictionary = dict_insert(dictionary,numerodelinhas,yytext,IKS_SIMBOLO_LITERAL_STRING);
				 else dict_insert(dictionary,numerodelinhas,yytext,IKS_SIMBOLO_LITERAL_STRING); return TK_LIT_STRING;}

"true"                           {if(dictionary == NULL) dictionary = dict_insert(dictionary,numerodelinhas,yytext,IKS_SIMBOLO_LITERAL_BOOL);
				 else dict_insert(dictionary,numerodelinhas,yytext,IKS_SIMBOLO_LITERAL_BOOL); return TK_LIT_TRUE;}

"false"                          {if(dictionary == NULL) dictionary = dict_insert(dictionary,numerodelinhas,yytext,IKS_SIMBOLO_LITERAL_BOOL);
				 else dict_insert(dictionary,numerodelinhas,yytext,IKS_SIMBOLO_LITERAL_BOOL); return TK_LIT_FALSE;}
     
-?[0-9]*\.[0-9]+                 {if(dictionary == NULL) dictionary = dict_insert(dictionary,numerodelinhas,yytext,IKS_SIMBOLO_LITERAL_FLOAT);
				 else dict_insert(dictionary,numerodelinhas,yytext,IKS_SIMBOLO_LITERAL_FLOAT); return TK_LIT_FLOAT;}

" "                                



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

. {return TOKEN_ERRO; }

					
%%

void init_me() {
    dictionary = dict_init();
    }
