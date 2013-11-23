#include "CodeGenerator.h"

void generateCode(ASTREE* program)
{
	TAC* code = program->scc[0]->code;

	generateARCode(code);

	printf("\n\nILOC:\n\n");
	ILOC_GEN(code);
	printf("\n\nEND\n\n");
}

/**
 * generateARCode:
 * Recebe o código gerado na primeira passagem pela árvore,
 * inclui o código para gerenciamento dos registros de ativação.
 */
void generateARCode(TAC* code)
{
	TAC* ptCode = code;
	TAC* ptCodeAnt;

	while(ptCode != NULL)
	{
		// quando o nodo atual for uma chamada de função, ou a própria main:
		if(ptCode->opcode == FUNCTION_CALL || ptCode->info == "main")
		{
			// procura a função na lista de funções:
			FunctionList* function = searchFunction(functionList, ptCode->info);
			if(function != NULL)
			{
				TAC* newCode = CodeGenerate_null();
				List* localVars = function->localVars;

				int lvSize = 0; // vai receber o tamanho necessário na pilha para as variáveis locais da função.
				while(localVars != NULL)
				{
					lvSize = lvSize + var_size(localVars->type);
					localVars = localVars->next;
				}

				//TODO: por enquanto, nesse ponto, já temos o tamanho das variáveis locais no registro de ativação.
				// falta inserir na lista de funções os outros parâmetros necessários e pegá-los aqui.
				// falta gerar o código necessário para o gerenciamento da pilha, utilizando esses dados.

				ptCodeAnt->next = newCode;
				newCode->next = ptCode;
			}
		}
		ptCodeAnt = ptCode;
		ptCode = ptCode->next;
	}
}

TAC* EndFuncCode(TAC* code){
/*
	TAC* aux;
	aux = CodeGenerate_null(); 
	aux->l1 = main_label;
	aux->opcode = ILOC_JUMPI;
	TAC* aux2 = code;
	code = aux;
	code->next = aux2;
	return code;
*/
	code = CodeGenerate_null();
	return code;
}

TAC* FunctionCall(ASTREE* node,TAC* code){
/*
	TAC* aux = code;

	list_print(FunctionsLabels);

	code = CodeGenerate_nop(node,code);

	registers = RegisterGenerate(registers); 
	aux = code;
	while(aux->next != NULL)
		aux = aux->next;
	aux->next = CodeGenerate_null();
	aux->next->r1 = FP;
	aux->next->r2 = registers;  
	aux->next->r3 = FP;
	labels = LabelGenerate(labels);
	aux->next->label = labels;
	aux->next->opcode = ILOC_ADD;

	aux = code;
	while(aux->next != NULL)
		aux = aux->next;
	aux->next = CodeGenerate_null(); 
	aux->next->l1 = main_label;
	aux->next->opcode = ILOC_JUMPI;
	aux = code;

	aux = code;
	while(aux->next != NULL)
		aux = aux->next;
	aux->next = CodeGenerate_null();
	aux->next->r1 = FP;
	aux->next->r2 = registers;  
	aux->next->r3 = FP;
	aux->next->opcode = ILOC_SUB;

	aux = code;
	while(aux->next != NULL)
		aux = aux->next;
	registers = RegisterGenerate(registers); 
	aux->next = CodeGenerate_null(); 
	aux->next->r3 = registers-1;
	aux->next->constant = FP_SIZE;	
	aux->next->opcode = ILOC_LOADI;

	return code;
*/

	node->code = CodeGenerate_null();
	node->code->opcode = FUNCTION_CALL;
	if(node->scc[0] != NULL)
		if(node->scc[0]->symbol != NULL)
			node->code->info = node->scc[0]->symbol->text;

	code = CODE_Insert(node);

	return code;
}


TAC* FramePointerInit(TAC* code){
/*
	TAC* aux = code;
	while(aux->next != NULL)
		aux = aux->next;
	aux->next = CodeGenerate_null(); 
	aux->next->l1 = main_label;
	aux->next->opcode = ILOC_JUMPI;
	aux = code;
	while(aux->next != NULL)
		aux = aux->next;
	aux->next = CodeGenerate_null();
	registers = 1;
	aux->next->r1 = registers;
	aux->next->r3 = FP;	
	aux->next->opcode = ILOC_STORE;
	aux = code;
	while(aux->next != NULL)
		aux = aux->next;
	aux->next = CodeGenerate_null(); 
	aux->next->r3 = 1;//registers;
	aux->next->constant = 600;	// initial value for fp
	aux->next->opcode = ILOC_LOADI;
	return code;
*/
	code = CodeGenerate_null();
	return code;
}

TAC* Function_link(ASTREE* node,TAC* code){

	node->code = CodeGenerate_null();
	node->code->opcode=ILOC_NOP;
	code = CODE_Insert(node);
	InsertLabel(node);
	if(strcmp(node->symbol->text,"main")==0)
	{
		main_label = labels;
		char* info = "main";
		code->info = info;
	}
	return code;
}

TAC* CodeGenerate_add(ASTREE* node,TAC* code){	
	code = TwoRegOper(node, ILOC_ADD);
	code = CODE_Insert(node);
	return code;
}

TAC* CodeGenerate_sub(ASTREE* node,TAC* code){
	code = TwoRegOper(node,ILOC_SUB);
	code = CODE_Insert(node); 
	return code;
}

TAC* CodeGenerate_mult(ASTREE* node,TAC* code){
	code = TwoRegOper(node, ILOC_MULT);
	code = CODE_Insert(node);
	return code;
}

TAC* CodeGenerate_div(ASTREE* node,TAC* code){
	code = TwoRegOper(node, ILOC_DIV);
	code = CODE_Insert(node);
	return code;
}

TAC* CodeGenerate_and(ASTREE* node,TAC* code){	
	code = TwoRegOper(node,ILOC_AND);
	code = CODE_Insert(node);
	return code;
}

TAC* CodeGenerate_or(ASTREE* node,TAC* code){	
	code = TwoRegOper(node,ILOC_OR);
	code = CODE_Insert(node);
	return code;
}

TAC* CodeGenerate_cmp_LT(ASTREE* node,TAC* code){	
	code = TwoRegOper(node, ILOC_CMP_LT);
	code = CODE_Insert(node);
	return code;
}

TAC* CodeGenerate_cmp_LE(ASTREE* node,TAC* code){	
	code = TwoRegOper(node, ILOC_CMP_LE);
	code = CODE_Insert(node);
	return code;
}

TAC* CodeGenerate_cmp_EQ(ASTREE* node,TAC* code){
	code = TwoRegOper(node, ILOC_CMP_EQ);
	code = CODE_Insert(node);
	return code;
}

TAC* CodeGenerate_cmp_GE(ASTREE* node,TAC* code){
	code = TwoRegOper(node, ILOC_CMP_GE);
	code = CODE_Insert(node); 
	return code;
}

TAC* CodeGenerate_cmp_GT(ASTREE* node,TAC* code){
	code = TwoRegOper(node, ILOC_CMP_GT);
	code = CODE_Insert(node);
	return code;
}

TAC* CodeGenerate_cmp_NE(ASTREE* node,TAC* code){	
	code = TwoRegOper(node, ILOC_CMP_NE);
	code = CODE_Insert(node);
	return code;
}

TAC* CodeGenerate_jumpI(ASTREE* node,TAC* code){
	node->code = CodeGenerate_null(); 
	node->code->l1 = labels;
	node->code->opcode = ILOC_JUMPI;
	code = CODE_Insert(node);
	return code;
}

TAC* CodeGenerate_nop(ASTREE* node,TAC* code){
	node->code=CodeGenerate_null();
	node->code->opcode = ILOC_NOP; 
	code = CODE_Insert(node);

	return code;
}

TAC* CodeGenerate_loadI(ASTREE* node, TAC* code){
	node->code = CodeGenerate_null(); 
	registers = RegisterGenerate(registers);
	node->code->r3 = registers;
	node->code->constant = atoi(node->symbol->text);
	node->code->opcode = ILOC_LOADI;
	code = CODE_Insert(node);
	return code;
}

TAC* CodeGenerate_loadAI(ASTREE* node, TAC* code){
	ASTREE* aux_t = node;
	if(node->type == IKS_AST_VETOR_INDEXADO){
		code = CodeGenerate_nop(node,code);
		code = code->next;
		i_reg = list_init();
		i_reg = list_insert(i_reg,aux_t->scc[1]->code->r3,0,"nop",0);
		aux_t=aux_t->scc[2];
		while(aux_t != NULL){
			i_reg = list_insert(i_reg,aux_t->scc[0]->code->r3,0,"nop",0);
			aux_t=aux_t->scc[1];
		}
		code = AddressCalc(node);
	}
	else{
		int flag;
		List* aux=list_lookup(GlobalDesloc,node->symbol->text);
		if( aux !=NULL)
			flag = BSS;
		else{
			aux = list_lookup(LocalDesloc,node->symbol->text);
			flag = FP;
		}
		if(aux != NULL){
			node->code = CodeGenerate_null(); 
			registers = RegisterGenerate(registers);
			node->code->r1 = flag;
			node->code->r3 = registers;
			if(aux != NULL) 
				node->code->constant = aux->tam; 
			node->code->opcode = ILOC_LOADAI;
			code = CODE_Insert(node);
		}
	}
	return code;
}

TAC* CodeGenerate_store(ASTREE* node, TAC* code){
	node->code = CodeGenerate_null();
	node->code->r1 = node->scc[1]->code->r3;
	node->code->r3 =node->scc[0]->code->r3;
	node->code->opcode = ILOC_STORE;
	if(node->scc[2] == NULL)
		code = CODE_Insert(node);
	else
		code = CODE_InsertCommand(node);
	return code;
}

TAC* CodeGenerate_cbr(ASTREE* node,TAC* code){
	node->code = CodeGenerate_null();
	node->code->r3 =node->scc[0]->code->r3;
	InsertLabel(node->scc[1]);
	if(node->scc[2] == NULL){
		node->scc[2] = (ASTREE*)malloc(sizeof(ASTREE));
		code=CodeGenerate_nop(node->scc[2],code);
	}
	InsertLabel(node->scc[2]);
	node->code->l1 = labels - 1;
	node->code->l2 = labels;
	node->code->next = NULL;
	node->code->opcode = ILOC_CBR;
	if(node->scc[3] == NULL)
		code = CODE_Insert_CBR_IF(node);
	else{
		InsertLabel(node->scc[3]);
		code = CodeGenerate_jumpI(node->scc[1],code);		
		code = CODE_Insert_CBR_IF_ELSE(node);
	}
	return code;
}

void VarDeslocGen(List* list, int id, List* el_num){
	List* list2 = list_copy(list2,list);
	List* aux = list2;
	int BeforeSize = 0;

	if(list != NULL){
		while(aux != NULL){
			aux->tam = BeforeSize;
			BeforeSize = var_size(aux->type)*(aux->size) + BeforeSize;
			aux = aux->next;
		}
		switch(id){
			case LOCAL: 	LocalDesloc  = list2;
					break;
			case GLOBAL:	GlobalDesloc = list2;
					ArrayDimmention = el_num;
					break;
		}
	}
}

void IsthereLabel(TAC* code){
	if(code->label != -1) 
		printf("L%d:\n",code->label);
}

void InsertLabel(ASTREE* node){
	TAC* aux = node->code;
	while(aux->next != NULL)
		aux = aux->next;
	labels = LabelGenerate(labels);
	aux->label = labels;
}

TAC* InvertCodeList(TAC* list){
	TAC* aux =list;
	TAC* inv_aux;
	TAC* inverted = NULL;
	while(list!= NULL){
		TAC* new = malloc(sizeof(TAC));
		new->r1 = list->r1;
		new->r2 = list->r2;
		new->r3 = list->r3;
		new->l1 = list->l1;
		new->l2 = list->l2;
		new->label = list->label;
		new->constant = list->constant;
		new->opcode = list->opcode;
		new->next = NULL;
		if(inverted == NULL)
			inverted = new;
		else{
			inv_aux = inverted;
			inverted = new;
			inverted->next = inv_aux;
		}
		list = list->next;
	}
	return inverted;
}

int Dk(int k, int reg, List *array_el){
	if(k == 1)
		return reg;
	else{ 
		int aux = reg;
		aux--;
		k--;	
		return Dk(k,aux,array_el->next)*array_el->size + reg;
	}
}

TAC* AddressCalc(ASTREE* node){
	List* auxiliar = list_copy(auxiliar,list_lookup(ArrayDimmention,node->scc[0]->symbol->text));
	List* aux = auxiliar;
	TAC* aux_code;
	int i=0;
	int aux_r;
	if(aux != NULL){
		aux = aux->next;
		while(strcmp(aux->text,"nop") == 0){
			aux = aux->next;
			i++;
		}
		aux->next = NULL;
		i++;
		aux = auxiliar;
		while(aux->next != NULL)
			aux = aux->next;
		auxiliar=list_remove(auxiliar,aux->text);
		aux = auxiliar;
		auxiliar=list_remove(auxiliar,aux->text);
		auxiliar = list_insert(auxiliar,aux->type,aux->tam,aux->text,aux->size);
	}
	aux_r = registers;
	TAC* New = NULL;
	auxiliar = InvertList(auxiliar);
	if(i>1){
		aux = auxiliar;
		while(aux != NULL){
			New =CodeGenerate_loadI_ac(New,aux->size);
			aux = aux->next;
		}
		New =  InvertCodeList(New);
		aux_code = node->code;
		node->code = New;
		node->code = TACConcat(node->code,aux_code);
	}
	node->code = KD(i,node->code,auxiliar);
	node->code = CodeGenerate_soma_mult(node->code,node->scc[0]->code->r3,registers,ILOC_ADD);
	return node->code;
}

TAC* KD(int k,TAC* CodeList, List*n){
	TAC* aux_code = CodeList;
	aux_code = InvertCodeList(aux_code);
	aux_code = aux_code->next;
	int w = var_size(n->type);
	int i = k;
	int n_reg = registers - k + 1;
	n_reg++;
	if(k>=2){

		CodeList = CodeGenerate_soma_mult(CodeList,i_reg->type,n_reg,ILOC_MULT);
		i_reg = i_reg->next;
		CodeList = CodeGenerate_soma_mult(CodeList,i_reg->type,registers,ILOC_ADD);
		if(k>=3){
			i = i - 2;
			while(i){
				n_reg++;
				CodeList = CodeGenerate_soma_mult(CodeList,n_reg,i_reg->type,ILOC_MULT);
				i_reg = i_reg->next;
				CodeList = CodeGenerate_soma_mult(CodeList,n_reg,i_reg->type,ILOC_ADD);
				i--;
			}

		}
	
	}
	CodeList = CodeGenerate_loadI_ac(CodeList,w);
	CodeList = CodeGenerate_soma_mult(CodeList,registers-1,registers,ILOC_MULT);
	return CodeList;
}

TAC* CodeGenerate_null(){
	TAC* New =(TAC*)malloc(sizeof(TAC));
	New->r1=-1;
	New->r2=-1;
	New->r3=-1;
//	New->r1=-1;
	New->l1=-1;
	New->l2=-1;
	New->label=-1;
	New->constant=-1;
	New->opcode = -1;
	New->next = NULL;
	New->info = NULL;
	return New;
}

TAC* CodeGenerate_soma_mult(TAC* list,int r1, int r2, int id){
	registers = RegisterGenerate(registers);
	TAC* code = CodeGenerate_null();
	code->r1 = r1;
	code->r2 = r2;
	code->r3 = registers;
	if(id== ILOC_ADD)
		code->opcode = ILOC_ADD;
	else if(id== ILOC_MULT)
		code->opcode = ILOC_MULT;
	TAC* aux = list;
	list = code;
	code->next = aux;
	return list;
}

TAC* CodeGenerate_loadI_ac(TAC* list,int constant){
	TAC* New = CodeGenerate_null();
	registers = RegisterGenerate(registers);
	New->r3 = registers;
	New->constant = constant;
	New->opcode = ILOC_LOADI;
	TAC* aux = list;
	list = New;
	New->next = aux;
	return list;
}

TAC* CodeGenerate_insert(TAC* list, TAC* code){
	TAC* aux = list; 
	if(list==NULL)
		list = code;
	else{
		while(aux->next != NULL)
			aux = aux->next;
		code->next = NULL;
		aux->next = code;
	}
	return list;
}

TAC* CodeGenerate_cbr_wd(ASTREE* node,TAC* code){
	TAC* aux;
	TAC* JUMP = CodeGenerate_null();JUMP->opcode = ILOC_JUMPI;
	node->code = CodeGenerate_null();
	node->code->r3 =node->scc[0]->code->r3;
	if(node->scc[2] == NULL){
		node->scc[2] = (ASTREE*)malloc(sizeof(ASTREE));
		code=CodeGenerate_nop(node->scc[2],code);
	}
	labels = LabelGenerate(labels);
	node->scc[0]->code->label = labels;
	JUMP->l1 = labels;
	InsertLabel(node->scc[1]);
	InsertLabel(node->scc[2]);
	node->code->l1 = labels - 1;
	node->code->l2 = labels;
	node->code->next = NULL;
	node->code->opcode = ILOC_CBR;
	aux = node->scc[1]->code;
	node->scc[1]->code = JUMP;
	JUMP->next = aux;
	node->code = CODE_Insert_CBR_IF(node);
	return code;
}

TAC* CodeGenerate_cbr_dw(ASTREE* node,TAC* code){
	TAC* aux;
	TAC* aux2;
	InsertLabel(node->scc[0]);
	TAC* JUMP = CodeGenerate_null();
	JUMP->opcode = ILOC_JUMPI;
	JUMP->l1 = labels;
	node->code = CodeGenerate_null();
	node->code->opcode = ILOC_CBR;
	if(node->scc[0]->type == IKS_AST_BLOCO)
		node->code->r3 = node->scc[0]->scc[0]->code->r3;
	else
		node->code->r3 = node->scc[0]->code->r3;
	node->code->l1 = labels;
	if(node->scc[2] == NULL){
		node->scc[2] = (ASTREE*)malloc(sizeof(ASTREE));
		code=CodeGenerate_nop(node->scc[2],code);
	}
	InsertLabel(node->scc[2]);
	node->code->l2 = labels;
	aux = node->code;
	node->code = JUMP;
	node->code->next = aux;
	node->code = CODE_InsertCommand(node);
	return node->code;
}

TAC* TAC_init(void){
	TAC* code = (TAC*)malloc(sizeof(TAC));
	code = NULL;
	return code;
}

TAC* TACConcat(TAC* fater,TAC* son){
	if(fater != NULL && son!= NULL){
		TAC* aux = fater;
		while(aux->next!= NULL)
			aux = aux->next;
		aux->next = son;
	}
	return fater;
}

TAC* CODE_Insert(ASTREE* node){
	int i;
	for(i=3;i>=0;i--)
		if(node->scc[i] != NULL)
			TACConcat(node->code,node->scc[i]->code);
	return node->code;
}

TAC* CODE_InsertCommand(ASTREE* node){
	TAC* aux;
	TACConcat(node->code,node->scc[1]->code);
	TACConcat(node->code,node->scc[0]->code);
	aux = node->code;
	node->code = node->scc[2]->code;
	TACConcat(node->code,aux); 
	return node->code;
}

TAC* CODE_Insert_CBR_IF(ASTREE* node){
	TAC* aux;
	ASTREE* aux_node = node;
	aux = node->code; 
	if(aux_node->scc[2] != NULL)
		node->code = aux_node->scc[2]->code;
	TACConcat(node->code,aux_node->scc[1]->code);
	TACConcat(node->code,aux);
	TACConcat(node->code,aux_node->scc[0]->code);
	return node->code;
}

TAC* CODE_Insert_CBR_IF_ELSE(ASTREE* node){
	TAC* aux;
	ASTREE* aux_node = node;
	aux = node->code;
	node->code = aux_node->scc[3]->code;
	TACConcat(node->code,aux_node->scc[2]->code);
	TACConcat(node->code,aux_node->scc[1]->code);
	TACConcat(node->code,aux);
	TACConcat(node->code,aux_node->scc[0]->code);
	return node->code;
}

TAC* TwoRegOper(ASTREE* node, int opcode){
	node->code = CodeGenerate_null(); 
	node->code->r1 = node->scc[0]->code->r3;
	node->code->r2 = node->scc[1]->code->r3;
	registers = RegisterGenerate(registers);
	node->code->r3 = registers;
	node->code->opcode = opcode;
	return node->code;
}

void ILOC_GEN(TAC* code){
	code = InvertCodeList(code);
	char *reg;
	while(code != NULL){
		switch(code->opcode){
		case ILOC_NOP:		IsthereLabel(code);puts("NOP");
					break;
		case ILOC_ADD:		IsthereLabel(code);
					if(code->r3 == FP)
						printf("\tadd\tfp, r%d  \t=> fp\n",code->r2);
					else
						printf("\tadd\tr%d, r%d  \t=> r%d\n",code->r1,code->r2,code->r3);
					break;
		case ILOC_SUB:		IsthereLabel(code);
					if(code->r3 == FP)
						printf("\tsub\tfp, r%d  \t=> fp\n",code->r2);
					else
						printf("\tsub\tr%d, r%d  \t=> r%d\n",code->r1,code->r2,code->r3);
					break;
		case ILOC_MULT:		IsthereLabel(code);		
					printf("\tmult\tr%d, r%d  \t=> r%d\n",code->r1,code->r2,code->r3);
					break;
		case ILOC_DIV:		IsthereLabel(code);
					printf("\tdiv\tr%d, r%d  \t=> r%d\n",code->r1,code->r2,code->r3);
					break;
		case ILOC_AND:		IsthereLabel(code);
					printf("\tand\tr%d, r%d  \t=> r%d\n",code->r1,code->r2,code->r3);
					break;	
		case ILOC_OR:		IsthereLabel(code);
					printf("\tor\tr%d, r%d  \t=> r%d\n",code->r1,code->r2,code->r3);
					break;		
		case ILOC_LOADI:	IsthereLabel(code);
					printf("\tloadI\t%d\t\t=> r%d\n",code->constant,code->r3);
					break;
		case ILOC_LOADAI:	IsthereLabel(code);
					if(code->constant==FP_RETURN_ADDRESS)
						printf("\tloadAI\tfp,%d\t\t=> r%d\n",FP_RETURN_ADDRESS,code->r3);
					else{
						/*if(code->r3 == FP)
							strcpy(reg,"fp");
						else
							strcpy(reg,"bss");
						printf("\tloadAI\t%s,%d\t\t=> r%d\n",reg,code->constant,code->r3);*/
						if(code->r1 == FP)
							printf("\tloadAI\tfp,%d\t\t=> r%d\n",code->constant,code->r3);
						else
							printf("\tloadAI\tbss,%d\t\t=> r%d\n",code->constant,code->r3);
					}
					break;
		case ILOC_LOADAO:	IsthereLabel(code);
					printf("\tloadAO\tfp,%d\t\t=> r%d\n",code->r1,code->r2);
					break;
		case ILOC_STORE :	IsthereLabel(code);
					if(code->r3 == FP)
						printf("\tstore\tr%d\t\t=> fp\n",code->r1);
					else
						printf("\tstore\tr%d\t\t=> r%d\n",code->r1,code->r3);
					break;
		case ILOC_JUMPI:	IsthereLabel(code);
					printf("\tjumpI\t\t\t-> L%d\n", code->l1);
					break;
		case ILOC_CMP_LT:	IsthereLabel(code);
					printf("\tcmp_LT\tr%d, r%d  \t=> r%d\n",code->r1,code->r2,code->r3);
					break;
		case ILOC_CMP_LE:	IsthereLabel(code);
					printf("\tcmp_LE\tr%d, r%d  \t=> r%d\n",code->r1,code->r2,code->r3);
					break;
		case ILOC_CMP_EQ:	IsthereLabel(code);
					printf("\tcmp_EQ\tr%d, r%d  \t=> r%d\n",code->r1,code->r2,code->r3);
					break;
		case ILOC_CMP_GE:	IsthereLabel(code);
					printf("\tcmp_GE\tr%d, r%d  \t=> r%d\n",code->r1,code->r2,code->r3);
					break;
		case ILOC_CMP_GT:	IsthereLabel(code);
					printf("\tcmp_GT\tr%d, r%d  \t=> r%d\n",code->r1,code->r2,code->r3);
					break;
		case ILOC_CMP_NE:	IsthereLabel(code);
					printf("\tcmp_NE\tr%d, r%d  \t=> r%d\n",code->r1,code->r2,code->r3);
					break;
		case ILOC_CBR:		IsthereLabel(code);
					printf("\tcbr\tr%d\t\t=> L%d, L%d\n",code->r3, code->l1,code->l2);
					break;
		}
		code = code->next;
	}
}



