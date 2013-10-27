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
int registers;
int labels;

TAC* CodeGenerate_nop(ASTREE* node,TAC* code);
TAC* CodeGenerate_add   (ASTREE* node,TAC* code);
TAC* CodeGenerate_sub   (ASTREE* node,TAC* code);
TAC* CodeGenerate_mult  (ASTREE* node,TAC* code);
TAC* CodeGenerate_div   (ASTREE* node,TAC* code);
TAC* CodeGenerate_and(ASTREE* node,TAC* code);
TAC* CodeGenerate_or(ASTREE* node,TAC* code);
TAC* CodeGenerate_loadI (ASTREE* node,TAC* code);
TAC* CodeGenerate_loadAI(ASTREE* node,TAC* code);
TAC* CodeGenerate_store (ASTREE* node, TAC* code);
TAC* CodeGenerate_cmp_LT(ASTREE* node,TAC* code);
TAC* CodeGenerate_cmp_LE(ASTREE* node,TAC* code);
TAC* CodeGenerate_cmp_EQ(ASTREE* node,TAC* code);
TAC* CodeGenerate_cmp_GE(ASTREE* node,TAC* code);
TAC* CodeGenerate_cmp_GT(ASTREE* node,TAC* code);
TAC* CodeGenerate_cmp_NE(ASTREE* node,TAC* code);
TAC* CommandLink (ASTREE* root);
ASTREE* InvertTree(ASTREE* root);
TAC* CodeGenerate_cbr(ASTREE* node,TAC* code);
void IsthereLabel(TAC* code);
ASTREE* TwoRegOper(ASTREE* node, int opcode);
void VarDeslocGen(List* list, int id);
TAC* TAC_init(void);
void CODE_print(TAC* code);
void InsertLabel(ASTREE* node);
TAC* CODE_Insert(ASTREE* node);
TAC* CODE_InsertCommand(ASTREE* node);
TAC* CODE_Insert_CBR(ASTREE* node);
TAC* TACConcat(TAC* fater,TAC* son);
void ILOC_GEN(TAC* code);
TAC* InvertCodeList(TAC* list);

#endif

