#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stddef.h>

#define DEBUG

struct stack *stack_new(size_t size)
{

	struct stack * stack = (struct stack *)malloc(sizeof(struct stack));
	if(stack == NULL)
	{
		printf("Could not allocate space for stack pointer\n");
		exit(-1);
	}
	/* in case size equals 0, we will allocate SIZE_DEFAULT bytes */
	switch(size)
	{
		case 0:
		stack->items = (uint32_t*)malloc(sizeof(uint32_t)*SIZE_DEFAULT);
		stack->size = SIZE_DEFAULT;
		break;
		default:
		stack->items = (uint32_t*)malloc(sizeof(uint32_t)*size);
		stack->size = size;
		break;
	}

	if(stack->items == NULL)
	{
		printf("Could not allocate space for stack items\n");
		exit(-1);
	}

	stack->n=0;
	return stack;
}

/* add 50% of the current capacity to the stack*/
void stack_realloc(struct stack * stack)
{

#ifdef DEBUG
	printf("Stack capacity improved to %ld\n", stack->size + stack->size/2);
#endif

	stack->items = (uint32_t*)realloc(stack->items, sizeof(uint32_t)*(stack->size + stack->size/2));
	stack->size = stack->size + stack->size/2;
}

/* remove 50% of the current capacity from the stack*/
void stack_dealloc(struct stack * stack)
{

#ifdef DEBUG
	printf("Stack capacity decreased to %ld\n", stack->size - stack->size/2);
#endif

	stack->items = (uint32_t*)realloc(stack->items, sizeof(uint32_t)*(stack->size - stack->size/2));
	stack->size = stack->size - stack->size/2;
}

void stack_add(struct stack * stack, uint32_t value)
{
	if(stack->n >= stack->size)
	{
		stack_realloc(stack);
	}

	stack->items[stack->n] = value;
	stack->n++;
}

uint32_t stack_remove(struct stack * stack)
{
	if(stack->size/2 - stack->n > 0)
	{
		stack_dealloc(stack);
	}
	stack->n--;

	return stack->items[stack->n];
}

void free_stack(struct stack * stack)
{
	free(stack->items);
	free(stack);
}

int main()
{
	struct stack * stack = stack_new(2);
	stack_add(stack, 1);
	stack_add(stack, 2);
	stack_add(stack, 3);
	stack_add(stack, 4);

	printf("last \t%d\n", stack_remove(stack));
	printf("\t%d\n", stack_remove(stack));
	printf("\t%d\n", stack_remove(stack));
	printf("first \t%d\n", stack_remove(stack));

	free_stack(stack);
	return 0;
}







