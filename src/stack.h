#ifndef _STACK_H_
#define _STACK_H_

#include <stdio.h>
#include <stdlib.h>

#include "../config.h"

/** Basic stack structure (auto malloc)
 * 
 * only store void pointer
 */

struct stack;
typedef struct stack stack;

// init_size == 0  =>  NULL
stack *stack_empty(const size_t init_size);

int stack_is_empty(const stack *s);

size_t stack_size(const stack *s);

void stack_print(const stack *s);

void stack_push(stack *s, void *ptr);

void *stack_pop(stack *s);

void stack_free(stack *s);

#endif // _STACK_H_
