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

#define GLOBAL 	 1
#define LOCAL  	 2
#define	BSS	-20
#define	FP	-21

typedef struct tac{

	int r1;
	int r2;
	int r3;
	int l1,l2;
	int label;
	int constant;
	int opcode;
	struct tac* next;	
	
}TAC;

List* LocalDesloc;
List* GlobalDesloc;
List* ArrayDimmention;
int registers;
int labels;

TAC* CodeGenerate_or(ASTREE* node,TAC* code);
TAC* CodeGenerate_nop(ASTREE* node,TAC* code);
TAC* CodeGenerate_add(ASTREE* node,TAC* code);
TAC* CodeGenerate_sub(ASTREE* node,TAC* code);
TAC* CodeGenerate_div(ASTREE* node,TAC* code);
TAC* CodeGenerate_and(ASTREE* node,TAC* code);
TAC* CodeGenerate_cbr(ASTREE* node,TAC* code);
TAC* CodeGenerate_mult(ASTREE* node,TAC* code);
TAC* CodeGenerate_jumpI(ASTREE* node,TAC* code);
TAC* CodeGenerate_loadI(ASTREE* node,TAC* code);
TAC* CodeGenerate_loadAI(ASTREE* node,TAC* code);
TAC* CodeGenerate_store(ASTREE* node, TAC* code);
TAC* CodeGenerate_cmp_LT(ASTREE* node,TAC* code);
TAC* CodeGenerate_cmp_LE(ASTREE* node,TAC* code);
TAC* CodeGenerate_cmp_EQ(ASTREE* node,TAC* code);
TAC* CodeGenerate_cmp_GE(ASTREE* node,TAC* code);
TAC* CodeGenerate_cmp_GT(ASTREE* node,TAC* code);
TAC* CodeGenerate_cmp_NE(ASTREE* node,TAC* code);

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


