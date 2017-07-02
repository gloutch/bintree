#include "pool.h"


struct pool {

  size_t size;
  size_t sizeof_content;

  int bool_gc; // using garbage collector;
  void (*free_func) (pool *, void *);
  
  struct stack *malloc_ptr;
  struct stack *free_pointer;
};


struct pool *pool_empty(const size_t sizeof_content, const size_t init_size) {

  if ((init_size == 0) || (sizeof_content == 0))
    return NULL;

  pool *p = malloc(sizeof(struct pool));
  if (p == NULL) {
    MALLOC_ERROR
    return NULL;
  }

  p->size       = init_size;
  p->sizeof_content = sizeof_content;
  p->bool_gc        = 0;
  p->malloc_ptr     = stack_empty(8);
  
  char *ptr = malloc(sizeof_content * init_size);
  if (ptr == NULL) {
    stack_free(p->malloc_ptr);
    free(p);
    MALLOC_ERROR
    return NULL;
  }
  stack_push(p->malloc_ptr, ptr);

  p->free_pointer = stack_empty(init_size);
  for (size_t i = 0; i < init_size; i++) {
    stack_push(p->free_pointer, ptr);
    ptr += sizeof_content;
  }
  
  return p;
}


size_t pool_nb_occupied(const pool *p) {
  return p->size - stack_size(p->free_pointer);
}


void pool_collector(pool *p, void (*free_func)(pool *p, void *data)) {
  p->bool_gc = 1;
  p->free_func = free_func;
}


// iterate on each slot the free_func (pool is full)
static void garbage_collector(pool *p) {
  
  int n = stack_size(p->malloc_ptr);
  // handmade stack
  void *area[n];
  size_t size[n];

  // initialisation of the stacks
  area[0] = stack_pop(p->malloc_ptr);
  size[0] = p->size / 2;
  if (n > 1) {
    for (int i = 1; i < n; i++) {
      area[i] = stack_pop(p->malloc_ptr);
      size[i] = size[i - 1] / 2;
    }
    size[n - 1] = size[n - 2];
  }
  
  // apply garbage collector
  for (int i = 0; i < n ; i++) {
    void *ptr = area[i];
    for (int j = 0; j < size[i]; j++) {
      (p->free_func)(p, ptr);
      ptr += p->sizeof_content;
    }
  }

  // rebuild p->malloc_ptr (in same order)
  for (int i = n - 1; 0 <= i; i--)
    stack_push(p->malloc_ptr, area[i]);
}

static void extend_pool(pool *p) {

  size_t n = p->size;
  char *ptr = malloc(p->sizeof_content * n);
  if (ptr == NULL) {
    MALLOC_ERROR;
  }
  stack_push(p->malloc_ptr, ptr);
  
  for (size_t i = 0; i < n; i++) {
    stack_push(p->free_pointer, ptr);
    ptr += p->sizeof_content;
  }
  p->size *= 2;
}

void *pool_slot(pool *p) {
  
  if (stack_is_empty(p->free_pointer)) {
    // pool is full
    if (p->bool_gc) {
      garbage_collector(p);
      if (stack_is_empty(p->free_pointer))
	extend_pool(p);
    } else
      extend_pool(p);
  }
  return stack_pop(p->free_pointer);
}


void pool_remove(pool *p, void *ptr) {
  stack_push(p->free_pointer, ptr);
}


void pool_free(pool *p) {

  while ( !stack_is_empty(p->malloc_ptr) )
    free(stack_pop(p->malloc_ptr));

  stack_free(p->malloc_ptr);
  stack_free(p->free_pointer);

  free(p);
}


