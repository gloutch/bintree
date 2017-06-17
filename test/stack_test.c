#include <stdio.h>
#include <assert.h>

#include "../src/stack.h"


void stack_empty_test() {
  printf("\t stack_empty_test \n");

  stack *s0 = stack_empty(0);
  assert(s0 == NULL);
  
  stack *s = stack_empty(1);
  assert(s != NULL);
  assert(stack_is_empty(s));
  assert(stack_size(s) == 0);
  stack_free(s);
}


void stack_memory_test() {
  printf("\t stack_memory_test \n");

  stack *s = stack_empty(3);

  int n = 8;
  for (int i = 0; i < n; i++) {
    assert(stack_size(s) == i);
    stack_push(s, &s + i);
  }
  assert(stack_size(s) == n);
  
  for (int i = n - 1; i >= 0; i--) {
    assert(stack_pop(s) == &s + i);
    assert(stack_size(s) == i);
  }
  
  stack_free(s);
}


int main(int argc, char *argv[]) {

  printf("stack_test: \n");
  stack_empty_test();
  stack_memory_test();
  
  return 0;
}
