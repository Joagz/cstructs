#ifndef STACK_H
#define STACK_H

#define SIZE_DEFAULT 64

#include <stdint.h>
#include <stddef.h>

struct stack {
	size_t size;
	size_t n;
	uint32_t *items;
};

void stack_add(struct stack * stack, uint32_t value);

uint32_t stack_remove(struct stack * stack);

void stack_free(struct stack * stack);

/* create a new stack, if size argument is zero (0) the stack size will be SIZE_DEFAULT */
struct stack *stack_new(size_t size);

#endif
