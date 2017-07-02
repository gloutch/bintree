#ifndef _POOL_H_
#define _POOL_H_

#include <stdlib.h>

#include "../config.h"
#include "stack.h"

/** Pool manager (auto malloc)
 *
 * Possibility of ~ garbage collector
 */

struct pool;
typedef struct pool pool;


// (init_size == 0 || sizeof_content == 0)  =>  NULL
pool *pool_empty(const size_t sizeof_content, const size_t init_size);

size_t pool_nb_occupied(const pool *p);

// enable tracing garbage collector using free_func that free unreachable element 
void pool_collector(pool *p, void (*free_func)(pool *p, void *data));

// return pointer to an allocated pool of sizeof_content bytes
void *pool_slot(pool *p);

// remove element at ptr
void pool_remove(pool *p, void *ptr);

void pool_free(pool *p);


#endif // _POOL_H_
