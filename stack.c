#include "stack.h"


struct stack {
  size_t max_size;
  size_t size;
  void **start;
};


stack *stack_empty(const size_t init_size) {

  if (init_size == 0)
    return NULL;

  stack *s = malloc(sizeof(struct stack));
  if (s == NULL) {
    MALLOC_ERROR
    return NULL;
  }

  s->max_size = init_size;
  s->size = 0;
  
  s->start = malloc(sizeof(void *) * init_size);
  if (s->start == NULL) {
    free(s);
    MALLOC_ERROR
    return NULL;
  }
  
  return s;
}


int stack_is_empty(const stack *s) {
  return (s->size == 0);
}


size_t stack_size(const stack *s) {
  return s->size;
}


void stack_print(const stack *s) {
  size_t n = s->size;
  printf("size: %zu \n", n);

  if (n != 0) {
    void **p = s->start;

    printf("> %p \n", p[-1]);
    for (size_t i = 2; i <= n; i++)
      printf("  %p \n", p[-i]);
  }
}


void stack_push(stack *s, void *ptr) {

  if (s->size == s->max_size) {
    
    s->max_size *= 2;
    s->start = realloc(s->start - s->size, sizeof(void *) * s->max_size);
    if (s->start == NULL) {
      MALLOC_ERROR;
      return;
    }
    s->start += s->size;
  }

  *(s->start) = ptr;
  (s->start)++;
  (s->size)++;
}


void *stack_pop(stack *s) {
  (s->start)--;
  (s->size)--;
  return *(s->start);
}


void stack_free(stack *s) {
  free(s->start - s->size);
  free(s);
}
