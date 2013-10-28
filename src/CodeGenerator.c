#include "CodeGenerator.h"

/*	add	r1, r2	=>	r3	
	sub	r1, r2	=>	r3	
	mult	r1, r2	=>	r3	
	div	r1, r2	=>	r3	
	and	r1, r2	=>	r3	
	or	r1, r2	=>	r3	
	loadI   c1	=>	r3		
	loadAI  r1,c2	=>	r3	
	store	r1	=>	r3		
	cbr     r3	=>	l1,l2		
	cmp_LT	r1, r2	=>	r3	
	cmp_LE	r1, r2	=>	r3	
	cmp_EQ	r1, r2	=>	r3	
	cmp_GE	r1, r2	=>	r3	
	cmp_GT	r1, r2	=>	r3	
	cmp_NE	r1, r2	=>	r3	
	oper 	r1, r2	=> 	r3
	r1,  	c2	=> 	r3		
*/	

TAC* CodeGenerate_add(ASTREE* node,TAC* code){	
	node = TwoRegOper(node, ILOC_ADD);
	code = CODE_Insert(node);
	return code;
}

TAC* CodeGenerate_sub(ASTREE* node,TAC* code){
	node = TwoRegOper(node,ILOC_SUB);
	code = CODE_Insert(node); 
	return code;
}

TAC* CodeGenerate_mult(ASTREE* node,TAC* code){
	node = TwoRegOper(node, ILOC_MULT);
	code = CODE_Insert(node);
	return code;
}

TAC* CodeGenerate_div(ASTREE* node,TAC* code){
	node = TwoRegOper(node, ILOC_DIV);
	code = CODE_Insert(node);
	return code;
}

TAC* CodeGenerate_and(ASTREE* node,TAC* code){	
	node = TwoRegOper(node,ILOC_AND);
	code = CODE_Insert(node);
	return code;
}

TAC* CodeGenerate_or(ASTREE* node,TAC* code){	
	node = TwoRegOper(node,ILOC_OR);
	code = CODE_Insert(node);
	return code;
}

TAC* CodeGenerate_loadI(ASTREE* node, TAC* code){
	registers = RegisterGenerate(registers);
	node->code = (TAC*)malloc(sizeof(TAC));
	node->code->r1 = -1;
	node->code->r2 = -1;
	node->code->r3 = registers;
	node->code->constant = atoi(node->symbol->text);
	node->code->label = -1;
	node->code->l1 = -1;
	node->code->l2 = -1;
	node->code->next = NULL;
	node->code->opcode = ILOC_LOADI;
	code = CODE_Insert(node);
	return code;
}

TAC* CodeGenerate_loadAI(ASTREE* node, TAC* code){
	int flag;
	List* aux;
	aux=list_lookup(GlobalDesloc,node->symbol->text);
	if( aux !=NULL)
		flag = BSS;
	else{
		aux = list_lookup(LocalDesloc,node->symbol->text);
		flag = FP;
	}
	registers = RegisterGenerate(registers);
	node->code = (TAC*)malloc(sizeof(TAC));
	node->code->r1 = flag;
	node->code->r2 = -1;
	node->code->r3 = registers;
	node->code->label = -1;
	node->code->l1 = -1;
	node->code->l2 = -1;
	node->code->constant = aux->tam; 
	node->code->next = NULL;
	node->code->opcode = ILOC_LOADAI;
	code = CODE_Insert(node);
	return code;
}

TAC* CodeGenerate_store(ASTREE* node, TAC* code){
	node->code = (TAC*)malloc(sizeof(TAC));
	node->code->r1 = node->scc[1]->code->r3;
	node->code->r2 = -1;
	node->code->r3 =node->scc[0]->code->r3;
	node->code->l1 = -1;
	node->code->l2 = -1;
	node->code->label = -1;
	node->code->constant = -1;
	node->code->next = NULL;
	node->code->opcode = ILOC_STORE;
	if(node->scc[2] == NULL)
		code = CODE_Insert(node);
	else
		code = CODE_InsertCommand(node);
	return code;
}


TAC* CodeGenerate_cbr(ASTREE* node,TAC* code){
	node->code = (TAC*)malloc(sizeof(TAC));
	node->code->r1 = -1;
	node->code->r2 = -1;
	node->code->r3 =node->scc[0]->code->r3;
	node->code->label = -1;
	node->code->constant = -1; 
	InsertLabel(node->scc[1]);
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

TAC* CodeGenerate_jumpI(ASTREE* node,TAC* code){
	node->code = (TAC*)malloc(sizeof(TAC));
	node->code->r1 = -1;
	node->code->r2 = -1;
	node->code->r3 = -1;
	node->code->l1 = labels;
	node->code->l2 = -1;
	node->code->label = -1;
	node->code->constant = -1;
	node->code->opcode = ILOC_JUMPI;
	node->code->next = NULL;
	code = CODE_Insert(node);
	return code;
}

TAC* CodeGenerate_cmp_LT(ASTREE* node,TAC* code){	
	node = TwoRegOper(node, ILOC_CMP_LT);
	code = CODE_Insert(node);
	return code;
}

TAC* CodeGenerate_cmp_LE(ASTREE* node,TAC* code){	
	node = TwoRegOper(node, ILOC_CMP_LE);
	code = CODE_Insert(node);
	return code;
}

TAC* CodeGenerate_cmp_EQ(ASTREE* node,TAC* code){
	node = TwoRegOper(node, ILOC_CMP_EQ);
	code = CODE_Insert(node);
	return code;
}

TAC* CodeGenerate_cmp_GE(ASTREE* node,TAC* code){
	node = TwoRegOper(node, ILOC_CMP_GE);
	code = CODE_Insert(node); 
	return code;
}

TAC* CodeGenerate_cmp_GT(ASTREE* node,TAC* code){
	node = TwoRegOper(node, ILOC_CMP_GT);
	code = CODE_Insert(node);
	return code;
}

TAC* CodeGenerate_cmp_NE(ASTREE* node,TAC* code){	
	node = TwoRegOper(node, ILOC_CMP_NE);
	code = CODE_Insert(node);
	return code;
}

TAC* CodeGenerate_nop(ASTREE* node,TAC* code){
	node->code = (TAC*)malloc(sizeof(TAC));
	node->code->r1 = -1;
	node->code->r2 = -1;
	node->code->r3 = -1;
	node->code->l1 = -1;
	node->code->l2 = -1;
	node->code->label = -1;
	node->code->constant = -1;
	node->code->opcode = ILOC_NOP;
	node->code->next = NULL;
	code = CODE_Insert(node);
	return code;
}

ASTREE* TwoRegOper(ASTREE* node, int opcode){
	node->code = (TAC*)malloc(sizeof(TAC));
	node->code->r1 = node->scc[0]->code->r3;
	node->code->r2 = node->scc[1]->code->r3;
	registers = RegisterGenerate(registers);
	node->code->r3 = registers;
	node->code->label = -1;
	node->code->l1 = -1;
	node->code->l2 = -1;
	node->code->constant = -1;
	node->code->opcode = opcode;
	node->code->next = NULL;
	return node;
}

TAC* TAC_init(void){
	TAC* code = (TAC*)malloc(sizeof(TAC));
	code = NULL;
	return code;
}

TAC* TACConcat(TAC* fater,TAC* son){
	TAC* aux = fater;
	while(aux->next!= NULL)
		aux = aux->next;
	aux->next = son;
	return fater;
}

TAC* CODE_Insert(ASTREE* node){
	int i;
	for(i=3;i>=0;i--){
		if(node->scc[i] != NULL)
			TACConcat(node->code,node->scc[i]->code);
	}
	return node->code;
}

TAC* CODE_InsertCommand(ASTREE* node){
	int i;
	TAC* aux;
	TACConcat(node->code,node->scc[0]->code);
	TACConcat(node->code,node->scc[1]->code);
	aux = node->code;
	node->code = node->scc[2]->code;
	TACConcat(node->code,aux);
	return node->code;
}

TAC* CODE_Insert_CBR_IF(ASTREE* node){
	int i;
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
	int i;
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

void CODE_print(TAC* code){
	TAC *aux = code; 
	while(aux !=NULL){
		printf("r1 = %d\n",aux->r1);
		printf("r2 = %d\n",aux->r2);
		printf("r3 = %d\n",aux->r3);
		printf("lab = %d\n",aux->label);
		printf("c2 = %d\n",aux->constant);
		printf("op = %d\n",aux->opcode);
		printf("l1 = %d\n",aux->l1);
		printf("l2 = %d\n",aux->l2);
		aux = aux->next;
	}
}

void VarDeslocGen(List* list, int id){
	/*Here we shall us the field type to 
	give the variable desloc information*/
	List* list2 = list_copy(list2,list);
	List* aux = list2;
	int BeforeSize = 0;
	if(list != NULL){
		while(aux != NULL){
			aux->tam = BeforeSize;
			BeforeSize = var_size(aux->type) + BeforeSize; 
			aux = aux->next;
		}
		switch(id){
			case LOCAL: 	LocalDesloc  = list2;break;
			case GLOBAL:	GlobalDesloc = list2;break;
		}
	}
}

void ILOC_GEN(TAC* code){
	code = InvertCodeList(code);
	char *reg;
	while(code != NULL){
		switch(code->opcode){
		case ILOC_NOP:		IsthereLabel(code);
					break;
		case ILOC_ADD:		IsthereLabel(code);
					printf("\tadd\tr%d, r%d  \t=> r%d\n",code->r1,code->r2,code->r3);
					break;
		case ILOC_SUB:		IsthereLabel(code);
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
					if(code->r1 == FP)
						strcpy(reg,"fp");
					else
						strcpy(reg,"bss");
					printf("\tloadAI\t%s, %d\t\t=> r%d\n",reg,code->constant,code->r3);
					break;
		case ILOC_STORE :	IsthereLabel(code);
					printf("\tstore\tr%d\t\t=> r%d\n",code->r1,code->r3);
					break;
		case ILOC_JUMPI:	IsthereLabel(code);
					printf("\tjumpI\t\t\t=> L%d\n", code->l1);
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
		case ILOC_CBR:		IsthereLabel(code);printf("\tcbr\tr%d\t\t=> L%d, L%d\n",code->r3, code->l1,code->l2);
					break;
		}
		code = code->next;
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
	TAC* inverted;
	TAC* inv_aux;
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

