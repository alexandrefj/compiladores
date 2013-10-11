#include "semantic.h"


	/*-----------------------------------------------ANALISE SEMANTICA-----------------------------------------------------------*/



void StackPopCommands(STACK* stack_pointer, List* global, List* global_vet, List* local, List* function_list, List* AllParams)
{
	
	if(stack_pointer!=NULL){ 

		List* InUseFunction  = TILL_NULL(function_list);	/*A ultima funcao da lista de funcoes sera a funcao em uso
										cujos comandos serao desempilhados*/
		
		int NumVal;	
		List *GlobalSearch, *LocalSearch, *VectorialSearch, *FunctionSearch, *aux;
		ASTREE* Variable,*RightSon,*LeftSon,*Left_RightGrandSon;

		switch(stack_pointer->disc->type){
		
		case IKS_AST_ARIM_SUBTRACAO:
		case IKS_AST_ARIM_MULTIPLICACAO: 
		case IKS_AST_LOGICO_E:
		case IKS_AST_LOGICO_OU:
		case IKS_AST_ARIM_DIVISAO:
		case IKS_AST_LOGICO_COMP_DIF:     
		case IKS_AST_LOGICO_COMP_IGUAL:   
		case IKS_AST_LOGICO_COMP_LE:      
		case IKS_AST_LOGICO_COMP_GE:      
		case IKS_AST_LOGICO_COMP_L:       
		case IKS_AST_LOGICO_COMP_G:       
		case IKS_AST_ARIM_SOMA:
						stack_pointer->disc->node_type = inference(stack_pointer->disc->scc[0]->node_type,stack_pointer->disc->scc[1]->node_type);
						break;

		case IKS_AST_CHAMADA_DE_FUNCAO:
						/*Primeiramente, teremos de verificar a existencia da função chamada*/
						
						LeftSon = stack_pointer->disc->scc[0];
						RightSon = stack_pointer->disc->scc[1]; 

						FunctionSearch = list_lookup(function_list,LeftSon->symbol->text); /*retorna a função chamada*/

						if(FunctionSearch != NULL){
							AllParams = FunctionParamList(AllParams,FunctionSearch->tam); /*Retorna a lista de parametros da função chamada*/
							Variable = ParamLookup(RightSon,AllParams);
		
							if(Variable == NULL && RightSon!= NULL)
								stack_pointer->disc->node_type = inference(RightSon->type,LeftSon->type);
							else if(Variable == NULL && RightSon == NULL)
								stack_pointer->disc->node_type = LeftSon->node_type;
						}
						else{
							printf("->Funcao nao declarada (linha %d)\n", getLineNumber()-1);
							exit(IKS_ERROR_UNDECLARED);
							break;
						}

						break;

		case IKS_AST_IDENTIFICADOR: 	

						GlobalSearch = list_lookup(global,stack_pointer->disc->symbol->text);
						LocalSearch  = list_lookup(local,stack_pointer->disc->symbol->text);
						VectorialSearch = list_lookup(global_vet,stack_pointer->disc->symbol->text); 
						FunctionSearch = list_lookup(function_list,stack_pointer->disc->symbol->text);

						if(GlobalSearch !=NULL){
							if(LocalSearch !=NULL){
								printf("->Identificador de variavel global foi declarado como variavel local (linha %d)\n", getLineNumber()-1);
								exit(IKS_ERROR_VARIABLE);
								break;
							}
							else if(FunctionSearch !=NULL){
								printf("->Identificador de variavel global foi declarado como funcao (linha %d)\n", getLineNumber()-1);
								exit(IKS_ERROR_VARIABLE);
								break;
							}
							else{
								stack_pointer->disc->node_type = GlobalSearch->type;
								stack_pointer->disc->size = var_size(stack_pointer->disc->node_type);
								break;
							}

						}
						else if(LocalSearch != NULL){
							if(GlobalSearch != NULL){
								printf("->Identificador de variavel local foi declarado como variavel global (linha %d)\n", getLineNumber()-1);
								exit(IKS_ERROR_VARIABLE);
								break;
							}
							else if(FunctionSearch != NULL){
								printf("->Identificador de variavel local foi declarado como funcao (linha %d)\n", getLineNumber()-1);
								exit(IKS_ERROR_VARIABLE);
								break;
							}
							else{
								stack_pointer->disc->node_type = LocalSearch->type;
								stack_pointer->disc->size = var_size(stack_pointer->disc->node_type);
								break;
							}

						}
						else if(FunctionSearch != NULL){
							if(GlobalSearch != NULL){
								printf("->Identificador de funcao foi declarado como variavel global (linha %d)\n", getLineNumber()-1);
								exit(IKS_ERROR_VARIABLE);
								break;
							}
							else if(LocalSearch !=NULL){
								printf("->Identificador de funcao foi declarado como variavel local (linha %d)\n", getLineNumber()-1);
								exit(IKS_ERROR_VARIABLE);
								break;
							}
							else{
								stack_pointer->disc->node_type = FunctionSearch->type;
								stack_pointer->disc->size = var_size(stack_pointer->disc->node_type);
								break;
							}
						}
						else if (VectorialSearch ==NULL){
							printf("->Identificador nao declarado (linha %d)\n", getLineNumber()-1);
							exit(IKS_ERROR_UNDECLARED);
							break;
						}
						break;

		case IKS_AST_LITERAL:
						stack_pointer->disc->node_type = stack_pointer->disc->symbol->type;
						stack_pointer->disc->size = var_size(stack_pointer->disc->symbol->type);
						break;

		case IKS_AST_VETOR_INDEXADO:	
						/*O primeiro filho de um vetor indexado será o TK_IDENTIFICADOR referente ao nome da variavel*/ 
				
						LeftSon = stack_pointer->disc->scc[0];		/*Variavel do vetor*/
						RightSon = stack_pointer->disc->scc[1];		/*Quantidade de termos do vetor*/


						GlobalSearch = list_lookup(global,stack_pointer->disc->scc[0]->symbol->text);
						LocalSearch  = list_lookup(local,stack_pointer->disc->scc[0]->symbol->text);
						VectorialSearch = list_lookup(global_vet,stack_pointer->disc->scc[0]->symbol->text);
						FunctionSearch = list_lookup(function_list,stack_pointer->disc->scc[0]->symbol->text);

					
						if(VectorialSearch !=NULL){

							LeftSon->node_type = VectorialSearch->type;
							stack_pointer->disc->node_type = VectorialSearch->type;		
							LeftSon->size =VectorialSearch->tam*var_size(LeftSon->node_type);
							stack_pointer->disc->size = LeftSon->size;
							
							break;
							
						}
						else
						{

							if(GlobalSearch !=NULL){
								printf("->Identificador de vetor foi declarado como variavel global (linha %d)\n", getLineNumber()-1);
								exit(IKS_ERROR_VARIABLE);
								break;
							}
							else if(LocalSearch !=NULL){
								printf("->Identificador de vetor foi declarado como variavel local (linha %d)\n", getLineNumber()-1);
								exit(IKS_ERROR_VARIABLE);
								break;
							}
		
							else if(FunctionSearch !=NULL){
								printf("->Identificador de vetor foi declarado como funcao (linha %d)\n", getLineNumber()-1);
								exit(IKS_ERROR_VARIABLE);
								break;
							}

						}
						break;

		case IKS_AST_ATRIBUICAO: 	

						/*Quando chegarmos no nó atribuição já teremos os nós filhos definidos: leftson e rightson
 									filho direito do filho da esquerda*/

						LeftSon = stack_pointer->disc->scc[0];	
						RightSon = stack_pointer->disc->scc[1];	
						Left_RightGrandSon = LeftSon->scc[1]; 
						
						if(stack_pointer->disc->scc[0]->type == IKS_AST_VETOR_INDEXADO){
							Variable = stack_pointer->disc->scc[0]->scc[0];

							GlobalSearch = list_lookup(global,Variable->symbol->text);
							LocalSearch  = list_lookup(local,Variable->symbol->text);
							VectorialSearch = list_lookup(global_vet,Variable->symbol->text);
							FunctionSearch = list_lookup(function_list,Variable->symbol->text);
			
										
							 if(GlobalSearch !=NULL){
								printf("-> Identificador de vetor foi declarado como variavel global (linha %d)\n", getLineNumber()-1);
								exit(IKS_ERROR_VARIABLE);
							 }
							 else if(FunctionSearch !=NULL){
								printf("-> Identificador de vetor foi declarado como funcao (linha %d)\n", getLineNumber()-1);
								exit(IKS_ERROR_FUNCTION);
							 }
							 else if(LocalSearch !=NULL){
								printf("-> Identificador de vetor foi declarado como variavel local (linha %d)\n", getLineNumber()-1);
								exit(IKS_ERROR_VARIABLE);
							 }
							 else{
								Left_RightGrandSon->node_type = coertion(IKS_INT,Left_RightGrandSon->node_type);
								stack_pointer->disc->node_type = inference(LeftSon->node_type,RightSon->node_type); /* atribuição de tipo ao nodo indexado*/
								
							 }
							 
						}
						else if(stack_pointer->disc->scc[0]->type == IKS_AST_IDENTIFICADOR){
							Variable = stack_pointer->disc->scc[0];

							GlobalSearch = list_lookup(global,Variable->symbol->text);
							LocalSearch  = list_lookup(local,Variable->symbol->text);
							VectorialSearch = list_lookup(global_vet,Variable->symbol->text);
							FunctionSearch = list_lookup(function_list,Variable->symbol->text);
							
							if(VectorialSearch !=NULL){
								printf("-> Identificador de variavel foi declarado como vetor (linha %d)\n", getLineNumber()-1);
								exit(IKS_ERROR_VECTOR);
							}
							else if(FunctionSearch !=NULL){
								printf("-> Identificador de variavel foi declarado como funcao (linha %d)\n", getLineNumber()-1);
								exit(IKS_ERROR_FUNCTION);
							}
							else
								stack_pointer->disc->node_type = coertion(LeftSon->node_type,RightSon->node_type);				
						}
						break;
		case IKS_AST_INPUT:		
						LeftSon = stack_pointer->disc->scc[0];

						if(LeftSon->type != IKS_AST_IDENTIFICADOR){
							printf("O parametro do comando input (linha %d) nao se trata de um identificador\n",getLineNumber()-1);
							exit(IKS_ERROR_WRONG_PAR_INPUT);			
						}
						else
							 stack_pointer->disc->node_type = LeftSon->node_type;				
						break;
		case IKS_AST_OUTPUT:		
						LeftSon = stack_pointer->disc->scc[0];

						if(LeftSon->node_type == IKS_CHAR){
							printf("O parametro do comando output (linha %d) deve ser literal string ou expressao\n",getLineNumber()-1);
							exit(IKS_ERROR_WRONG_PAR_INPUT);			
						}
						else
							 stack_pointer->disc->node_type = LeftSon->node_type;	
						break;

		case IKS_AST_RETURN:
						LeftSon = stack_pointer->disc->scc[0];
			
						if(InUseFunction->type != LeftSon->node_type){

							if((LeftSon->node_type == IKS_CHAR) ||(LeftSon->node_type == IKS_STRING)){
								printf("A variavel do comando return deve ter o mesmo tipo da funcao %s (linha %d)\n",InUseFunction->text,getLineNumber()-1);
								exit(IKS_ERROR_WRONG_PAR_RETURN);
							}
							else{
								InUseFunction->type = coertion(InUseFunction->type,LeftSon->node_type);
							}	stack_pointer->disc->node_type = LeftSon->node_type;
						}
						else{
							stack_pointer->disc->node_type = LeftSon->node_type;
						}
						break;   



		}
		stack_pointer= stack_pointer->next;
		return  StackPopCommands(stack_pointer,global,global_vet,local,function_list, AllParams);
	}
}


ASTREE* ParamLookup(ASTREE* param_i, List* param_list){

	/*Precisaremos fazer um caminhamento a direita da arvore*/

	List* ListNode;

	if(param_i == NULL && param_list==NULL) /*chegou ao fim dos parametros*/
	{ 
		return NULL;
	}
	else if(param_i== NULL && param_list!= NULL)
	{
		printf("Faltando argumentos na função (linha %d)\n", getLineNumber()-1);
		exit(IKS_ERROR_MISSING_ARGS);
	}
	else if(param_i!= NULL && param_list== NULL)
	{
		printf("Excesso de argumentos na funcao (linha %d)\n", getLineNumber()-1);
		exit(IKS_ERROR_EXCESS_ARGS);
	}
	else if(param_list->type == param_i->symbol->type)
	{

		param_i = param_i->scc[0];
		param_list = param_list->next;
		return  ParamLookup(param_i,param_list);
	}	
	else if(inference_three(param_list->type,param_i->symbol->type))
	{
		param_i->symbol->type = inference_three(param_list->type,param_i->symbol->type);
		param_i = param_i->scc[0];
		param_list = param_list->next;
		return  ParamLookup(param_i,param_list);
	}
	else
	{	
		printf("Argumentos com tipos nao condizentes (linha %d)\n", getLineNumber()-1);
		exit(IKS_ERROR_WRONG_TYPE_ARGS);
	}
}


List* FunctionListInsert(List* function_list,DICT_NODE* node, int type, int size){

	if(list_lookup(function_list,node->text)==NULL){
		function_list=list_insert(function_list,type,size,node->text);
	} 
	else{
		printf("->Redeclaracao de funcao (linha %d)\n", getLineNumber());
		exit(IKS_ERROR_DECLARED);
	}

	return function_list;
}

List* GlobalVarListInsert(List* list,DICT_NODE* node,int control,int type, int size){

	switch(control){

		case GLOBAL_VAR_DEC_IDENTIFIER_CONTROL:		if(list_lookup(list,node->text)==NULL)
									list=list_insert(list,type,size,node->text); 
								else{
									printf("->Redeclaracao de variavel global (linha = %d)\n", getLineNumber());
									exit(IKS_ERROR_DECLARED);
								}
								
								break;

		case GLOBAL_VET_DEC_IDENTIFIER_CONTROL:		if(list_lookup(list,node->text)==NULL){
									list=list_insert(list,type,size,node->text);
								}
								else{
									printf("->Redeclaracao de vetor (linha %d)\n", getLineNumber());
									exit(IKS_ERROR_DECLARED); 
								}
								break;
	}

	return list;
}


List* LocalVarListInsert(List* local_var,DICT_NODE* node, int type, int size, List* function_list){

	if(list_lookup(local_var,node->text)==NULL){
		local_var=list_insert(local_var,type,size,node->text);
	} 
	else{
		printf("->Redeclaracao de variavel local (linha %d)\n", getLineNumber());
		exit(IKS_ERROR_DECLARED);
	}
	
	return local_var;
}


int var_size(int id)
{
	switch(id)
	{
	case IKS_INT: 		return 4;break;
	case IKS_FLOAT: 	return 8;break;
	case IKS_BOOL: 		return 1;break;
	case IKS_CHAR: 		return 1;break;
	case IKS_STRING: 	return 1;break;
	}
}


int coertion(int x, int exp){
/*Quando é necessario atribuir a x uma expressao de outro tipo
	retorna o tipo da exp apos a coerção	*/

	if(x==exp)
		return x;
	else if(x==IKS_FLOAT && exp==IKS_INT)
		return IKS_FLOAT;
	else if(x==IKS_INT && exp==IKS_FLOAT)
		return IKS_INT; 		
	else if(x==IKS_FLOAT && exp==IKS_BOOL)
		return IKS_FLOAT;		
	else if(x==IKS_BOOL && exp==IKS_FLOAT)
		return IKS_BOOL;	
	else if(x==IKS_INT && exp==IKS_BOOL)
		return IKS_INT;
	else if(x==IKS_BOOL && exp==IKS_INT)
		return IKS_BOOL;
	else if(exp==IKS_STRING){
		printf("Impossivel fazer coerção para o tipo String (linha %d)\n", getLineNumber()-1);
		exit(IKS_ERROR_STRING_TO_X);	
	}
	else if(exp==IKS_CHAR){
		printf("Impossivel fazer coerção para o tipo Char (linha %d)\n", getLineNumber()-1);
		exit(IKS_ERROR_CHAR_TO_X);	
	}
	else if(x==IKS_STRING || x==IKS_CHAR ){
		printf("Tipos incompativeis (linha %d)\n", getLineNumber()-1);
		exit(IKS_ERROR_WRONG_TYPE);	
	}
}


int inference(int val1, int val2)  
{				  
	if(val1==val2)
		return val1;
	else if((val1==IKS_INT && val2==IKS_FLOAT) || (val2==IKS_INT && val1==IKS_FLOAT))
		return IKS_FLOAT;
	else if((val1==IKS_INT && val2==IKS_BOOL) || (val2==IKS_INT && val1==IKS_BOOL))
		return IKS_INT;
	else if((val1==IKS_BOOL && val2==IKS_FLOAT) || (val2==IKS_BOOL && val1==IKS_FLOAT))
		return IKS_FLOAT;
	else if(val2==IKS_STRING)
	{
		printf("Impossivel fazer coerção para o tipo String (linha %d)\n", getLineNumber()-1);
		exit(IKS_ERROR_STRING_TO_X);	
	}
	else if(val2==IKS_CHAR)
	{
		printf("Impossivel fazer coerção para o tipo Char (linha %d)\n", getLineNumber()-1);
		exit(IKS_ERROR_CHAR_TO_X);	
	}
	else if(val1==IKS_STRING)
	{
		printf("Tipos incompativeis (linha %d)\n", getLineNumber()-1);
		exit(IKS_ERROR_WRONG_TYPE);	
	}
	else if(val1==IKS_CHAR)
	{
		printf("Tipos incompativeis (linha %d)\n", getLineNumber()-1);
		exit(IKS_ERROR_WRONG_TYPE);	
	}
}

int inference_three(int val1, int val2)
{
	if(val1==val2)
		return val1;

	else if(val1==IKS_INT && val2==IKS_INT)
		return IKS_INT;

	else if(val1==IKS_FLOAT && val2==IKS_FLOAT)
		return IKS_FLOAT;

	else if(val1==IKS_BOOL && val2==IKS_BOOL)
		return IKS_BOOL;

	else if((val1==IKS_INT && val2==IKS_FLOAT) || (val2==IKS_INT && val1==IKS_FLOAT))
		return IKS_FLOAT;

	else if((val1==IKS_INT && val2==IKS_BOOL) || (val2==IKS_INT && val1==IKS_BOOL))
		return IKS_INT;

	else if((val1==IKS_BOOL && val2==IKS_FLOAT) || (val2==IKS_BOOL && val1==IKS_FLOAT))
		return IKS_FLOAT;
	else if(val2==IKS_STRING)
		return 0;
	
	else if(val2==IKS_CHAR)
		return 0;
}

/*




#define IKS_AST_PROGRAMA             0
#define IKS_AST_FUNCAO               1
#define IKS_AST_IF_ELSE              2
#define IKS_AST_DO_WHILE             3
#define IKS_AST_WHILE_DO             4


#define IKS_AST_BLOCO                9
#define IKS_AST_ARIM_INVERSAO       16 // - (operador unário -)
#define IKS_AST_LOGICO_COMP_NEGACAO 25 // !
#define      26 // para var[exp] quando o índice exp é acessado no vetor var
#define  27

*/
