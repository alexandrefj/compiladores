#include "semantic.h"
int flag1 = 0;
List* FunctionListInsert(List* function_list,DICT_NODE* node, int type, int size){

	if(list_lookup(function_list,node->text)==NULL){
		function_list=list_insert(function_list,type,size,node->text);
	} 
	else{
		printf("->Redeclaracao da funcao (linha %d)\n", getLineNumber());
		exit(IKS_ERROR_DECLARED);
	}

	return function_list;
}

List* GlobalVarListInsert(List* list,DICT_NODE* node,int control,int type, int size){

	switch(control){

		case GLOBAL_VAR_DEC_IDENTIFIER_CONTROL:		if(list_lookup(list,node->text)==NULL)
									list=list_insert(list,type,size,node->text); 
								else{
									printf("-Redeclaracao de variavel global (linha = %d)\n", getLineNumber());
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


void StackPopCommands(STACK* stack_pointer,List* global, List* global_vet, List* local,List* function_list)
{


	
	if(stack_pointer!=NULL){ 

		List* InUseFunction  = TILL_NULL(function_list);	/*A ultima funcao da lista de funcoes sera a funcao em uso
										cujos comandos serao desempilhados*/


		if(stack_pointer->disc->type==11 || stack_pointer->disc->type==10)
			printf("%s\n", stack_pointer->disc->symbol->text);
		else
			printf("%d\n", stack_pointer->disc->type);
		
		
		puts("------------------------------------------------------------------------");//printf("------------  %d \n",local->type);
			printf("Funcoes\n");list_print(function_list);printf("Tipo da funcao %d Nome %s \n\n",InUseFunction->type,InUseFunction->text);
			printf("Variaveis Globais\n");list_print(global);printf("  \n");
			printf("Variaveis locais\n");list_print(local);printf("  \n");
			printf("Variaveis vetoriais\n");list_print(global_vet);printf("  \n");
		puts("------------------------------------------------------------------------");

		int flag = 0;
		int NumVal;	
		List *GlobalSearch, *LocalSearch, *VectorialSearch, *FunctionSearch;
		ASTREE* Variable,*RightSon,*LeftSon;

		switch(stack_pointer->disc->type){
		
		case IKS_AST_ARIM_SUBTRACAO:
		case IKS_AST_ARIM_MULTIPLICACAO: break;
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
						stack_pointer->disc->size = var_size(stack_pointer->disc->node_type);
						break;

		case IKS_AST_IDENTIFICADOR: 	
						
						/*A partir da variavel flag, determinaremos se o identificador está na lista de:
						variaveis globais 	(flag=1)
						lista de vetores 	(flag=2),
						lista de locais 	(flag=3)
						ou lista de funcoes 	(flag=4)*/

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
								flag = 1;
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
								flag = 3;
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
								flag = 4;
								stack_pointer->disc->node_type = FunctionSearch->type;
								stack_pointer->disc->size = var_size(stack_pointer->disc->node_type);
								break;
							}
						}
					/*	else if(VectorialSearch !=NULL){
								printf("->Identificador nao vetorial foi declarado como vetor (linha %d)\n", getLineNumber()-1);
								exit(IKS_ERROR_VARIABLE);
								break;
						}*/
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
							flag = 2;
							LeftSon->node_type = VectorialSearch->type;
							stack_pointer->disc->node_type = VectorialSearch->type;		
							LeftSon->size =VectorialSearch->tam*var_size(LeftSon->node_type);
							stack_pointer->disc->size = LeftSon->size;
							
							break;
							
						}
						else{

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
						LeftSon = stack_pointer->disc->scc[0];		/*Quando chegarmos no nó atribuição,*/
						RightSon = stack_pointer->disc->scc[1];	/*Já teremos os nós filhos definidos: leftson e rightson*/
						
						
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
								stack_pointer->disc->node_type = inference(RightSon->node_type,LeftSon->node_type);
								stack_pointer->disc->size= var_size(stack_pointer->disc->node_type);
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
							else{
								stack_pointer->disc->node_type = inference(RightSon->node_type,LeftSon->node_type);
								stack_pointer->disc->size= var_size(stack_pointer->disc->node_type);							
							}
						}

							

						break;



		}
		stack_pointer= stack_pointer->next;
		return  StackPopCommands(stack_pointer,global,global_vet,local,function_list);
	}
}



/*
STACK* expression_identifier(stack_pointer,i){

	STACK* aux = stack_pointer;
	
	stack_pointer = stack_pointer->next;
	//inferency(stack_pointer,-1);
	stack_pointer->disc->size = var_size(stack_pointer->disc->symbol->type);

	stack_pointer = stack_pointer->next;
	//inferency(stack_pointer,-1);
	stack_pointer->disc->size = var_size(stack_pointer->disc->symbol->type);

	//inferency(stack_pointer, stack_pointer->ant);

	

}*/
int var_size(int id)
{
	switch(id){
	case IKS_INT: return 4;break;
	case IKS_FLOAT: return 8;break;
	case IKS_BOOL: return 1;break;
	case IKS_CHAR: return 1;break;
	case IKS_STRING: return 1;break;
	}
}


int inference(int val1, int val2)
{

	if(val1==IKS_INT && val2==IKS_INT)
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
	else if(val1==IKS_STRING || val2==IKS_STRING){
		printf("Impossivel fazer coerção para o tipo String (linha %d)\n", getLineNumber()-1);
		exit(IKS_ERROR_STRING_TO_X);	
	}
	else if(val1==IKS_CHAR || val2==IKS_CHAR){
		printf("Impossivel fazer coerção para o tipo Char (linha %d)\n", getLineNumber()-1);
		exit(IKS_ERROR_CHAR_TO_X);	
	}



}

/*


#define IKS_SIMBOLO_INT    1
#define IKS_SIMBOLO_FLOAT  2
#define IKS_SIMBOLO_CHAR   3
#define IKS_SIMBOLO_STRING 4
#define IKS_SIMBOLO_BOOL   5


IKS_AST_CHAMADA_DE_FUNCAO
#define IKS_AST_PROGRAMA             0
#define IKS_AST_FUNCAO               1
#define IKS_AST_IF_ELSE              2
#define IKS_AST_DO_WHILE             3
#define IKS_AST_WHILE_DO             4
#define IKS_AST_INPUT                5
#define IKS_AST_OUTPUT               6
#define IKS_AST_RETURN               8
#define IKS_AST_BLOCO                9
#define IKS_AST_ARIM_INVERSAO       16 // - (operador unário -)
#define IKS_AST_LOGICO_COMP_NEGACAO 25 // !
#define      26 // para var[exp] quando o índice exp é acessado no vetor var
#define  27

*/
