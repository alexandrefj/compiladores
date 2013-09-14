#include "comp_tree.h"

ASTREE *astCreate(int type, DICT_NODE *symbol, ASTREE *s0, ASTREE *s1, ASTREE *s2, ASTREE *s3)
{
	ASTREE *newNode;
	
	newNode = (ASTREE*)calloc(1,sizeof(ASTREE));
	newNode->type = type;
	newNode->symbol = symbol;
	newNode->scc[0] = s0;
	newNode->scc[1] = s1;
	newNode->scc[2] = s2;
	newNode->scc[3] = s3;
	//newNode->impresso = 0;
	return newNode;
}

/*
void *astPrintTree(ASTREE *root)
{
	int i;
	if(root==NULL) return;
	astPrintNode(root);
	for(i=0; i<MAX_NODE; i++)
	   astPrintTree(root->scc[i]);
}

void *astPrintNode(ASTREE *node)
{
	if(node==NULL) return;
	if(node->impresso==1)return;
	node->impresso = 1;
	switch(node->type)
	{	
            case AST_ADD:
		astPrintNode(node->scc[0]);		     
		fprintf(ExitTree," + ");
		astPrintNode(node->scc[1]);		            	
            	break;
            case AST_SUB:
		astPrintNode(node->scc[0]);		
		fprintf(ExitTree," - ");
		astPrintNode(node->scc[1]);		
            	break;
            case AST_MUL:
		astPrintNode(node->scc[0]);		
		fprintf(ExitTree," * ");
		astPrintNode(node->scc[1]);		
            	break;
            case AST_DIV:
		astPrintNode(node->scc[0]);		
		fprintf(ExitTree," / ");
		astPrintNode(node->scc[1]);		
            	break;
            case AST_KW_WORD:
		fprintf(ExitTree,"word");
		break;
            case AST_KW_BOOL:
		fprintf(ExitTree,"bool");
		break;
            case AST_KW_BYTE:
		fprintf(ExitTree,"byte");
		break;
            case AST_KW_IF:
		fprintf(ExitTree,"if (");
		astPrintNode(node->scc[0]);		
		fprintf(ExitTree,")\nthen ");
		astPrintNode(node->scc[1]);		
		break;
            case AST_KW_IF_ELSE:
		fprintf(ExitTree,"if (");
		astPrintNode(node->scc[0]);		
		fprintf(ExitTree,")\nthen ");
		astPrintNode(node->scc[1]);		 
		fprintf(ExitTree,"\nelse ");
		astPrintNode(node->scc[2]);		
		break;
            case AST_KW_LOOP:
		fprintf(ExitTree,"loop (");
		astPrintNode(node->scc[0]);		
		fprintf(ExitTree,") \n");
		astPrintNode(node->scc[1]);		
		break;
            case AST_KW_INPUT:
		if(node->symbol)
			if(node->symbol->text)
			{
				fprintf(ExitTree,"input %s", node->symbol->text);
			}
		break;
            case AST_KW_OUTPUT:
		fprintf(ExitTree,"output ");
		astPrintNode(node->scc[0]);		
		break;
            case AST_KW_RETURN:
		fprintf(ExitTree,"return ");
		astPrintNode(node->scc[0]);		
		break;
            case AST_OPERATOR_LE:
		astPrintNode(node->scc[0]);		
		fprintf(ExitTree," <= ");
		astPrintNode(node->scc[1]);		
            	break;
            case AST_OPERATOR_GE:
		astPrintNode(node->scc[0]);		
		fprintf(ExitTree," >= ");
		astPrintNode(node->scc[1]);		
            	break;
            case AST_OPERATOR_EQ:
		astPrintNode(node->scc[0]);		
		fprintf(ExitTree," == ");
		astPrintNode(node->scc[1]);		
            	break;
            case AST_OPERATOR_NE:
		astPrintNode(node->scc[0]);		
		fprintf(ExitTree," != ");
		astPrintNode(node->scc[1]);		
            	break;
            case AST_OPERATOR_AND:
		astPrintNode(node->scc[0]);		
		fprintf(ExitTree," && ");
		astPrintNode(node->scc[1]);		
            	break;
            case AST_OPERATOR_OR:
		astPrintNode(node->scc[0]);		
		fprintf(ExitTree," || ");
		astPrintNode(node->scc[1]);		
            	break;	
	    case AST_TK_IDENTIFIER_EC:
		if(node->symbol)
			if(node->symbol->text)
			{
				fprintf(ExitTree,"&");				
				fprintf(ExitTree, "%s", node->symbol->text);
			}	
            	break;	
	    case AST_TK_IDENTIFIER_ASTE:
		if(node->symbol)
			if(node->symbol->text)
			{
				fprintf(ExitTree,"*");
				fprintf(ExitTree, "%s", node->symbol->text);
			}		
            	break;												
            case AST_LIT_INTEGER:
		if(node->symbol)
			if(node->symbol->intVal >= 0 || node->symbol->intVal < 0)
			{        
				fprintf(ExitTree, "%d ", node->symbol->intVal);
			}
		break;
            case AST_LIT_TRUE:
		fprintf(ExitTree," TRUE ");
		break;
            case AST_LIT_FALSE:
		fprintf(ExitTree," FALSE ");
		break;
            case AST_LIT_CHAR:
		if(node->symbol)
			if(node->symbol->charVal)
			{
				fprintf(ExitTree, "'%c'", node->symbol->charVal);
			}
		break;
            case AST_LIT_STRING:
	  	fprintf (ExitTree, "\"");
	  	fprintf (ExitTree, "%s", node->symbol->text);
	  	fprintf (ExitTree, "\"");
	  	break;
            case AST_TK_IDENTIFIER:
		if(node->symbol)
			if(node->symbol->text)
			{
				fprintf(ExitTree, "%s", node->symbol->text);
			}
		break;
            case AST_IGUAL:
		astPrintNode(node->scc[0]);		
		fprintf(ExitTree," = ");
		astPrintNode(node->scc[1]);		
            	break;
            case AST_MAIOR:
		astPrintNode(node->scc[0]);		
		fprintf(ExitTree," > ");
		astPrintNode(node->scc[1]);		
            	break;
            case AST_MENOR:
		astPrintNode(node->scc[0]);		
		fprintf(ExitTree," < ");
		astPrintNode(node->scc[1]);		
            	break;
            case AST_NEG:
		fprintf(ExitTree," ! ");
		astPrintNode(node->scc[0]);		
            	break;
            case AST_exprComParent:
		fprintf(ExitTree," (");
		astPrintNode(node->scc[0]);		
		fprintf(ExitTree,") ");
            	break;
	    case AST_exprComChavesTK_IDENTIFIER:
		if(node->symbol)
			if(node->symbol->text)
			{
				fprintf(ExitTree, "%s", node->symbol->text);
			}
		fprintf(ExitTree," [");
		astPrintNode(node->scc[0]);		
		fprintf(ExitTree,"] ");
            	break;
	    case AST_exprComParFuncTK_IDENTIFIER:
		if(node->symbol)
			if(node->symbol->text)
			{
				fprintf(ExitTree, "%s", node->symbol->text);
			}
		fprintf(ExitTree," (");
		astPrintNode(node->scc[0]);		
		fprintf(ExitTree,") ");
            	break;
	    case AST_exprComPartTK_IDENTIFIER:
		if(node->symbol)
			if(node->symbol->text)
			{
				fprintf(ExitTree, "%s", node->symbol->text);
			}
		fprintf(ExitTree," (");
		astPrintNode(node->scc[0]);		
		fprintf(ExitTree,") ");
            	break;
	    case AST_programa:
		astPrintNode(node->scc[0]); 
	    	break;
	    case AST_declaracao_glob:
		astPrintNode(node->scc[0]);
		fprintf(ExitTree,"\n");
		astPrintNode(node->scc[1]);
		break;
	    case AST_declaracao_local:
		astPrintNode(node->scc[0]);
		fprintf(ExitTree,"\n");
		astPrintNode(node->scc[1]);
		break;
	    case AST_ATRIB_CONST:
	    if(node->symbol)
			if(node->symbol->text)
			{
				fprintf(ExitTree, " %s ", node->symbol->text);				
				fprintf(ExitTree, " = ");				
				astPrintNode(node->scc[0]);	
			}
	    break;
	    case AST_ATRIB_VET:
	    if(node->symbol)
			if(node->symbol->text)
			{
				fprintf(ExitTree, " %s ", node->symbol->text);				
				fprintf(ExitTree, " [ ");
				astPrintNode(node->scc[0]);
				fprintf(ExitTree, " ] = ");				
				astPrintNode(node->scc[1]);	
			}
	    break;
	    case AST_declaracao_var:
		if(node->symbol)
			if(node->symbol->text)
			{
				astPrintNode(node->scc[0]);	
				fprintf(ExitTree, " %s :", node->symbol->text);				
				astPrintNode(node->scc[1]);	
				fprintf(ExitTree, ";\n");
			}
		break;
	    case AST_declaracao_vetch:
		if(node->symbol)
			if(node->symbol->text)
			{
				astPrintNode(node->scc[0]);	
				fprintf(ExitTree, " %s ", node->symbol->text);
				fprintf(ExitTree, "[ ");				
				astPrintNode(node->scc[1]);	
				fprintf(ExitTree, "] : ");	
				astPrintNode(node->scc[2]);			
				fprintf(ExitTree, ";\n");
			}
		break;
            case AST_declaracao_vet:
		if(node->symbol)
			if(node->symbol->text)
			{
				astPrintNode(node->scc[0]);	
				fprintf(ExitTree, " %s ", node->symbol->text);
				fprintf(ExitTree, "[ ");				
				astPrintNode(node->scc[1]);	
				fprintf(ExitTree, "] ");		
				fprintf(ExitTree, ";\n");
			}
		break;
            case AST_declaracao_pointer:
		if(node->symbol)
			if(node->symbol->text)
			{
				astPrintNode(node->scc[0]);	
				fprintf(ExitTree, " $");
				fprintf(ExitTree, "%s", node->symbol->text);
				fprintf(ExitTree, " : ");				
				astPrintNode(node->scc[1]);	
				fprintf(ExitTree, ";\n");
			}
		break;
	    case AST_funcao:
		if(node->symbol)
			if(node->symbol->text)
			{
				astPrintNode(node->scc[0]);	
				fprintf(ExitTree, " %s", node->symbol->text);
				fprintf(ExitTree," (");
				astPrintNode(node->scc[1]);	
				fprintf(ExitTree,") \n\n");
				astPrintNode(node->scc[2]);	
				astPrintNode(node->scc[3]);	
			}
		break;
	    case AST_vaiParaParametros:
		fprintf(ExitTree,", ");
		astPrintNode(node->scc[0]);
		astPrintNode(node->scc[1]);
		break;
	    case AST_Parametros:
		astPrintNode(node->scc[0]);
		astPrintNode(node->scc[1]);
		break;
	    case AST_parametro:
		if(node->symbol)
			if(node->symbol->text)
			{
				astPrintNode(node->scc[0]);
				fprintf(ExitTree, " %s", node->symbol->text);
			}
		
		break;
	    case AST_bloco:
		fprintf(ExitTree,"{\n");
		astPrintNode(node->scc[0]);	
		fprintf(ExitTree,"\n}");
		break;
	    case AST_cmd:
		astPrintNode(node->scc[0]);	
		break;
	    case AST_outp:
		astPrintNode(node->scc[0]);	
		break;
	    case AST_outp2:
		astPrintNode(node->scc[0]);	
		fprintf(ExitTree, ",");
		astPrintNode(node->scc[1]);	
		break;
	    case AST_primary_expression:
		astPrintNode(node->scc[0]);	
		break;
	   case AST_val_vet:
		astPrintNode(node->scc[0]);
		astPrintNode(node->scc[1]);
		break;
	    case AST_params_func:
		astPrintNode(node->scc[0]);	
		fprintf(ExitTree,", ");
		astPrintNode(node->scc[1]);	
		break;
	    case AST_cmds:
		astPrintNode(node->scc[0]);	
		fprintf(ExitTree,";\n");
		astPrintNode(node->scc[1]);	
		break;
	    default: 
		printf("UNKNOWN\n");
	    	break;
	}
*/
