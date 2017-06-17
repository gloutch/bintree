#ifndef _MEMORY_H_
#define _MEMORY_H_

#include <stdlib.h>

#include "../config.h"
#include "stack.h"

/** Pool manager (auto malloc)
 *    No error management
 */

struct memory;
typedef struct memory memory;


// (init_size == 0 || sizeof_content == 0)  =>  NULL
memory *memo_empty(const size_t sizeof_content, const size_t init_size);

size_t memo_nb_elem(const memory *memo);

// return pointer to an allocated memory of sizeof_content bytes
void *memo_new_ptr(memory *memo);

// remove element at ptr
void memo_remove(memory *memo, void *ptr);

void memo_free(memory *memo);


#endif // _MEMORY_H_
