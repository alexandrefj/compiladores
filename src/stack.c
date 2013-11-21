#include<stdlib.h>
#include<stdio.h>
#include "stack.h"
#include <string.h>
#include <iks_ast.h>



STACK* stack_init(void)
{
	STACK* stack = malloc(sizeof(STACK*));
	stack = NULL;
	return stack;
}


STACK* invert_stack(STACK* stack){

	while(stack->ant != NULL)
		stack = stack->ant;

	return stack;

}


STACK* stack_push(STACK* stack_pointer, ASTREE* three_node)
{

	STACK* new = malloc(sizeof(STACK*));
	new->disc = three_node;
	new->next = NULL;
	new->ant = NULL;


	if(stack_pointer != NULL){ 
		new->ant = stack_pointer;
		stack_pointer->next = new;
	}
		
	stack_pointer = new;

	return stack_pointer;
}

