#include "memory.h"


struct memory {

  size_t max_size;
  size_t sizeof_content;
  
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

  memo->max_size = init_size;
  memo->sizeof_content = sizeof_content;
  memo->malloc_ptr = stack_empty(8);
  
  char *ptr = malloc(sizeof_content * init_size);
  if (ptr == NULL) {
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


size_t memo_nb_elem(const memory *memo) {
  return memo->max_size - stack_size(memo->free_pointer);
}


void *memo_new_ptr(memory *memo) {
  if (stack_is_empty(memo->free_pointer)) {

    size_t n = memo->max_size;

    char *ptr = malloc(memo->sizeof_content * n);
    if (ptr == NULL) {
      MALLOC_ERROR;
      return NULL;
    }
    stack_push(memo->malloc_ptr, ptr);

    for (size_t i = 0; i < n; i++) {
      stack_push(memo->free_pointer, ptr);
      ptr += memo->sizeof_content;
    }
    memo->max_size += n;
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


