#include <stdio.h>
#include <assert.h>

#include "../src/memory.h"


void memory_empty_test() {
  printf("\t memory_empty_test \n");

  memory *m0 = memo_empty(0, 1);
  assert(m0 == NULL);

  memory *m00 = memo_empty(1, 0);
  assert(m00 == NULL);

  memory *m = memo_empty(1, 2);
  assert(m != NULL);
  assert(memo_nb_occupied(m) == 0);
  memo_free(m);
}


void memory_fill_test() {
  printf("\t memory_fill_test \n");

  memory *m = memo_empty(sizeof(char), 2);

  char *t1 = memo_slot(m);
  assert(memo_nb_occupied(m) == 1);
  *t1 = 'a';

  char *t2 = memo_slot(m);
  assert(memo_nb_occupied(m) == 2);
  *t2 = 'b';

  memo_remove(m, t1);
  memo_remove(m, t2);
  assert(memo_nb_occupied(m) == 0);
  
  assert(memo_slot(m) == t2);
  assert(memo_slot(m) == t1);
  assert(memo_nb_occupied(m) == 2);
  
  memo_free(m);
}


void memory_overflow_test() {
  printf("\t memory_overflow_test \n");

  int n = 8;
  char tab[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
  char *ptrs[] = {0, 0, 0, 0, 0, 0, 0, 0};
  
  memory *m = memo_empty(sizeof(char), 2);

  for (int i = 0; i < n; i++) {
    assert(memo_nb_occupied(m) == i);
    ptrs[i] = memo_slot(m);
    *(ptrs[i]) = tab[i];
  }
  for (int i = 0; i < n; i++) {
    memo_remove(m, ptrs[i]);
    assert(memo_nb_occupied(m) == n - i - 1);
  }
  assert(memo_nb_occupied(m) == 0);
  
  memo_free(m);
}


void strategy_int_test(memory *m, void *data) {
  if (*(int *) data == 0)
    memo_remove(m, data);
}

void memory_gc_test() {
  printf("\t memory_garbage_collector_test \n");
  
  memory *m = memo_empty(sizeof(int), 1);
  memo_collector(m, strategy_int_test);

  int n = 8;
  int *ptrs[n];
  for (int i = 0; i < n; i++) {
    ptrs[i] = memo_slot(m); // there are 4 malloced areas, 
    *ptrs[i] = 1;              // no value at 0
  }
  assert(memo_nb_occupied(m) == n);
  
  *ptrs[0] = 0;
  *ptrs[1] = 0;
  *ptrs[3] = 0;
  *ptrs[5] = 0;
  *ptrs[7] = 0;
  // next memo_slot need a malloc, try to free slot instead
  
  int *p = memo_slot(m);
  memo_remove(m, p);
  assert(memo_nb_occupied(m) == (n - 5));
  
  memo_free(m);
}


int main(int argc, char *argv[]) {
  
  printf("memory_test \n");
  memory_empty_test();
  memory_fill_test();
  memory_overflow_test();
  memory_gc_test();
  
  return 0;
}
