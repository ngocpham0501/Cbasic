#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char element_type;
typedef struct SNode {
  element_type element;
  struct SNode *link;
} SNode;

typedef struct stack_type$ {
  SNode *top;
} stack_type;

//initialize a stack
stack_type *iniStack(stack_type *stack) {
  stack = (stack_type *)malloc(sizeof(stack_type));
  stack->top = NULL;
  return stack;
}

int empty(stack_type *stack) {
  return stack->top == NULL;
}

SNode *makeSNode(element_type val) {
  SNode *p;
  p = (SNode *)malloc(sizeof(SNode));
  p->element = val;
  p->link = NULL;
  return p;
}

void push(element_type val, stack_type *stack) {
  int i;
  SNode *p;
  p = makeSNode(val);
  p->link = stack->top;
  stack->top = p;
}

element_type pop(stack_type *stack) {
  SNode *p;
  element_type val;
  if (empty(stack))
  {
    printf("Stack overflow\n");
    exit(0);
  }
  val = stack->top->element;
  p = stack->top;
  stack->top = stack->top->link;
  free(p);
  return val;
}

