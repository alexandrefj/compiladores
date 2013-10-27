#include "Label.h"

int LabelGenerate(int Labels){return ++Labels;}
/*
LABEL* LabInit(void){
	LABEL* lab = (LABEL*)calloc(1,sizeof(LABEL*));
	lab = NULL;
	return lab;
}

LABEL* CreateNewLabel(LABEL* lab){
	LABEL* new = malloc(sizeof(LABEL*));
	new->id = 0;
	new->next = NULL;
	if(lab == NULL){
		lab = new;
		return lab;
	}
	else{
		new->id = lab->id + 1;
		new->next = lab;
		return new;
	}	
}

*/
