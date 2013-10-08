#include <stdio.h>
#include <stdlib.h>
#include <comp_tree.h>
#include <comp_list.h>

#ifndef STACK_H
#define STACK_H

typedef struct stack
{
  ASTREE* disc;
  struct stack* next;
  struct stack* ant;
} 
STACK;

STACK* invert_stack(STACK* stack);
STACK* stack_init(void);
STACK* stack_push(STACK* stack_pointer, ASTREE* three_node);

#endif
