#include <stdio.h>
#include <assert.h>

#include "../src/pool.h"


void pool_empty_test() {
  printf("\t pool_empty \n");

  pool *m0 = pool_empty(0, 1);
  assert(m0 == NULL);

  pool *m00 = pool_empty(1, 0);
  assert(m00 == NULL);

  pool *m = pool_empty(1, 2);
  assert(m != NULL);
  assert(pool_nb_occupied(m) == 0);
  pool_free(m);
}


void pool_fill_test() {
  printf("\t pool_fill \n");

  pool *m = pool_empty(sizeof(char), 2);

  char *t1 = pool_slot(m);
  assert(pool_nb_occupied(m) == 1);
  *t1 = 'a';

  char *t2 = pool_slot(m);
  assert(pool_nb_occupied(m) == 2);
  *t2 = 'b';

  pool_remove(m, t1);
  pool_remove(m, t2);
  assert(pool_nb_occupied(m) == 0);
  
  assert(pool_slot(m) == t2);
  assert(pool_slot(m) == t1);
  assert(pool_nb_occupied(m) == 2);
  
  pool_free(m);
}


void pool_overflow_test() {
  printf("\t pool_overflow \n");

  int n = 8;
  char tab[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
  char *ptrs[] = {0, 0, 0, 0, 0, 0, 0, 0};
  
  pool *m = pool_empty(sizeof(char), 2);

  for (int i = 0; i < n; i++) {
    assert(pool_nb_occupied(m) == i);
    ptrs[i] = pool_slot(m);
    *(ptrs[i]) = tab[i];
  }
  for (int i = 0; i < n; i++) {
    pool_remove(m, ptrs[i]);
    assert(pool_nb_occupied(m) == n - i - 1);
  }
  assert(pool_nb_occupied(m) == 0);
  
  pool_free(m);
}


void strategy_int_test(pool *m, void *data) {
  if (*(int *) data == 0)
    pool_remove(m, data);
}

void pool_gc_test() {
  printf("\t pool_garbage_collector \n");
  
  pool *m = pool_empty(sizeof(int), 1);
  pool_collector(m, strategy_int_test);

  int n = 8;
  int *ptrs[n];
  for (int i = 0; i < n; i++) {
    ptrs[i] = pool_slot(m); // there are 4 malloced areas, 
    *ptrs[i] = 1;           // no value at 0
  }
  assert(pool_nb_occupied(m) == n);
  
  *ptrs[0] = 0;
  *ptrs[1] = 0;
  *ptrs[3] = 0;
  *ptrs[5] = 0;
  *ptrs[7] = 0;
  // next pool_slot need a malloc, try to free slot instead
  
  int *p = pool_slot(m);
  pool_remove(m, p);
  assert(pool_nb_occupied(m) == (n - 5));
  
  pool_free(m);
}


int main(int argc, char *argv[]) {
  
  printf("pool_test \n");
  pool_empty_test();
  pool_fill_test();
  pool_overflow_test();
  pool_gc_test();
  
  return 0;
}
