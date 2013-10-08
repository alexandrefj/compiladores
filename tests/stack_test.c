#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main(){

	ASTREE* root,*ast1,*ast2,*ast3,*ast4,*ast5,*ast6,*ast7;
	STACK *stack_pointer=stack_init();

	ast1=astCreate(1,0,0,0,0,0);
	stack_pointer = stack_push(stack_pointer,ast1);

	ast2=astCreate(2,0,0,0,0,0);
	stack_pointer = stack_push(stack_pointer,ast2);
	ast3=astCreate(3,0,0,0,0,0);
	stack_pointer = stack_push(stack_pointer,ast3);
	ast4=astCreate(4,0,0,0,0,0);
	stack_pointer = stack_push(stack_pointer,ast4);
	ast5=astCreate(5,0,ast4,0,0,0);
	stack_pointer = stack_push(stack_pointer,ast5);
	ast6=astCreate(6,0,0,0,0,0);
	stack_pointer = stack_push(stack_pointer,ast6);
	ast7=astCreate(7,0,ast5,ast6,0,0);
	stack_pointer = stack_push(stack_pointer,ast7);

	//stack_pop(stack_pointer,NULL,NULL,NULL,0);



return 0;
}
