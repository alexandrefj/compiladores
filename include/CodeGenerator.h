#include <stdio.h>
#include <stdlib.h>
#include "iks_ast.h"
#include "Registers.h"
#include "comp_tree.h"
#include "comp_list.h"
#include "iloc_simb.h"
#include "Label.h"

#ifndef CodeGenerator_H
#define CodeGenerator_H

#define FP_SIZE	 112
#define FP_RETURN_ADDRESS	 48
#define GLOBAL 	 1
#define LOCAL  	 2
#define	BSS	-20
#define	FP	-21
#define SP	-22
#define RX	-23

typedef struct tac{

	int r1;
	int r2;
	int r3;
	int l1,l2;
	int label;
	int constant;
	int opcode;
	char* info;
	struct tac* next;	
	
}TAC;

List* i_reg;
List* LocalDesloc;
List* GlobalDesloc;
List* ArrayDimmention;
List* FunctionsLabels;
int registers;
int labels;
int main_label;

FunctionList* functionList;
void generateCode(ASTREE* program);
void generateARCode(TAC* code);

TAC* EndFuncCode(TAC* code);

TAC* FramePointerInit(TAC* code);

TAC* FunctionCall(ASTREE* node,TAC* code);

TAC* Function_link(ASTREE* node,TAC* code);

TAC* CodeGenerate_or(ASTREE* node,TAC* code);
TAC* CodeGenerate_nop(ASTREE* node,TAC* code);
TAC* CodeGenerate_add(ASTREE* node,TAC* code);
TAC* CodeGenerate_sub(ASTREE* node,TAC* code);
TAC* CodeGenerate_div(ASTREE* node,TAC* code);
TAC* CodeGenerate_and(ASTREE* node,TAC* code);
TAC* CodeGenerate_cbr(ASTREE* node,TAC* code);
TAC* CodeGenerate_mult(ASTREE* node,TAC* code);
TAC* CodeGenerate_jumpI(ASTREE* node,TAC* code);
TAC* CodeGenerate_jump(ASTREE* node,TAC* code);
TAC* CodeGenerate_loadI(ASTREE* node,TAC* code);
TAC* CodeGenerate_loadAI(ASTREE* node,TAC* code);
TAC* CodeGenerate_store(ASTREE* node, TAC* code);
TAC* CodeGenerate_cmp_LT(ASTREE* node,TAC* code);
TAC* CodeGenerate_cmp_LE(ASTREE* node,TAC* code);
TAC* CodeGenerate_cmp_EQ(ASTREE* node,TAC* code);
TAC* CodeGenerate_cmp_GE(ASTREE* node,TAC* code);
TAC* CodeGenerate_cmp_GT(ASTREE* node,TAC* code);
TAC* CodeGenerate_cmp_NE(ASTREE* node,TAC* code);
TAC* CodeGenerate_cbr_wd(ASTREE* node,TAC* code);
TAC* CodeGenerate_storeCall(ASTREE* node, TAC* code);
TAC* CodeGenerate_storeCall2(ASTREE* node, TAC* code);

TAC* CodeGenerate_cbr_dw(ASTREE* node,TAC* code);

TAC* KD(int k,TAC* CodeList, List*n);
TAC* CodeGenerate_soma_mult(TAC* list,int r1, int r2, int id);
TAC* CodeGenerate_loadI_ac(TAC* list,int constant);
TAC* CodeGenerate_insert(TAC* list, TAC* code);

//TAC* CodeGenerate_valorRetorno(ASTREE* node,TAC* code);

void ILOC_GEN(TAC* code);
void IsthereLabel(TAC* code);
void InsertLabel(ASTREE* node);
int Dk(int k, int reg, List *array_el);
void VarDeslocGen(List* list, int id, List* el_num);

TAC* TAC_init(void);
TAC* CodeGenerate_null();
TAC* AddressCalc(ASTREE* node);
TAC* CODE_Insert(ASTREE* node);
TAC* InvertCodeList(TAC* list);
TAC* TACConcat(TAC* fater,TAC* son);
TAC* CODE_InsertCommand(ASTREE* node);
TAC* CODE_Insert_CBR_IF(ASTREE* node);
TAC* ArrayCodeGen(int e1,int n2,int e2);
TAC* TwoRegOper(ASTREE* node, int opcode);
TAC* CODE_Insert_CBR_IF_ELSE(ASTREE* node);

#endif


