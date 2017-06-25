#include "memory.h"


struct memory {

  size_t size;
  size_t sizeof_content;

  int bool_gc; // using garbage collector;
  void (*strategy) (memory *, void *);
  
  struct stack *malloc_ptr;
  struct stack *free_pointer;
};


struct memory *memo_empty(const size_t sizeof_content, const size_t init_size) {

  if ((init_size == 0) || (sizeof_content == 0))
    return NULL;

  memory *memo = malloc(sizeof(struct memory));
  if (memo == NULL) {
    MALLOC_ERROR
    return NULL;
  }

  memo->size       = init_size;
  memo->sizeof_content = sizeof_content;
  memo->bool_gc        = 0;
  memo->malloc_ptr     = stack_empty(8);
  
  char *ptr = malloc(sizeof_content * init_size);
  if (ptr == NULL) {
    stack_free(memo->malloc_ptr);
    free(memo);
    MALLOC_ERROR
    return NULL;
  }
  stack_push(memo->malloc_ptr, ptr);

  memo->free_pointer = stack_empty(init_size);
  for (size_t i = 0; i < init_size; i++) {
    stack_push(memo->free_pointer, ptr);
    ptr += sizeof_content;
  }
  
  return memo;
}


size_t memo_nb_occupied(const memory *memo) {
  return memo->size - stack_size(memo->free_pointer);
}


void memo_collector(memory *memo, void (*strategy)(memory *, void *)) {
  memo->bool_gc = 1;
  memo->strategy = strategy;
}


// iterate on each slot the strategy (memo is full)
static void garbage_collector(memory *memo) {
  
  int n = stack_size(memo->malloc_ptr);
  // handmade stack
  void *area[n];
  size_t size[n];
  
  area[0] = stack_pop(memo->malloc_ptr);
  size[0] = memo->size / 2;
  if (n > 1) {
    for (int i = 1; i < n; i++) {
      area[i] = stack_pop(memo->malloc_ptr);
      size[i] = size[i - 1] / 2;
    }
    size[n - 1] = size[n - 2];
  }
  
  // apply garbage collector
  for (int i = 0; i < n ; i++) {
    void *ptr = area[i];
    for (int j = 0; j < size[i]; j++) {
      (memo->strategy)(memo, ptr);
      ptr += memo->sizeof_content;
    }
  }

  // rebuild memo->malloc_ptr (in same order)
  for (int i = n - 1; 0 <= i; i--)
    stack_push(memo->malloc_ptr, area[i]);
}

static void extend_memo(memory *memo) {

  size_t n = memo->size;
  char *ptr = malloc(memo->sizeof_content * n);
  if (ptr == NULL) {
    MALLOC_ERROR;
  }
  stack_push(memo->malloc_ptr, ptr);
  
  for (size_t i = 0; i < n; i++) {
    stack_push(memo->free_pointer, ptr);
    ptr += memo->sizeof_content;
  }
  memo->size *= 2;
}

void *memo_slot(memory *memo) {
  
  if (stack_is_empty(memo->free_pointer)) {
    // memo is full
    if (memo->bool_gc) {
      garbage_collector(memo);
      if (stack_is_empty(memo->free_pointer))
	extend_memo(memo);
    } else
      extend_memo(memo);
  }

  return stack_pop(memo->free_pointer);
}


void memo_remove(memory *memo, void *ptr) {
  stack_push(memo->free_pointer, ptr);
}


void memo_free(memory *memo) {

  while ( !stack_is_empty(memo->malloc_ptr) )
    free(stack_pop(memo->malloc_ptr));

  stack_free(memo->malloc_ptr);
  stack_free(memo->free_pointer);

  free(memo);
}


