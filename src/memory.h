#ifndef _MEMORY_H_
#define _MEMORY_H_

#include <stdlib.h>

#include "../config.h"
#include "stack.h"

/** Pool manager (auto malloc)
 *
 * Possibility of ~ garbage collector
 */

struct memory;
typedef struct memory memory;


// (init_size == 0 || sizeof_content == 0)  =>  NULL
memory *memo_empty(const size_t sizeof_content, const size_t init_size);

size_t memo_nb_occupied(const memory *memo);

// enable tracing garbage collector using function strategy that free unreachable element 
void memo_collector(memory *memo, void (*strategy)(memory *, void *));

// return pointer to an allocated memory of sizeof_content bytes
void *memo_slot(memory *memo);

// remove element at ptr
void memo_remove(memory *memo, void *ptr);

void memo_free(memory *memo);


#endif // _MEMORY_H_
