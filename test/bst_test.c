#include <stdio.h>
#include <assert.h>

#include "../src/bst.h"


static int intcmp(const void *int1, const void *int2) {
  return (*(int *) int1) - (*(int *) int2);
}

void bst_test_new() {
  printf("\t bst_new \n");

  bst *b0 = bst_new(0, 1, NULL);
  assert(b0 == NULL);

  bst *b1 = bst_new(1, 0, NULL);
  assert(b1 == NULL);

  bst *b = bst_new(1, 1, NULL);
  assert(b != NULL);
  assert(bst_size(b) == 0);
  bst_free(b);
}

void bst_test_add() {
  printf("\t bst_add \n");

  bst *b = bst_new(sizeof(int), 2, intcmp);

  int n = 9;
  for (int i = 0; i < n; i++) {
    assert(bst_size(b) == i);
    *(int *) bst_add(b, &i) = i;
  }
  for (int i = 0; i < n; i++) {
    assert( bst_find(b, &i));
  }
  
  for (int i = n; i < 100; i++) {
    int j = -i;
    assert(!bst_find(b, &i));
    assert(!bst_find(b, &j));
  }
  
  bst_free(b);
}

void bst_rm_test() {
  printf("\t bst_rm \n");

  bst *b = bst_new(sizeof(int), 6, intcmp);

  int n = 12;
  int tab[] = {5, 2, 0, -1, 1, 3, 4, 7, 6, 9, 8, 10};
  for (int i = 0; i < n; i++)
    *(int *) bst_add(b, &(tab[i])) = tab[i];

  assert(bst_size(b) == n);
  for (int i = 0; i < n; i++)
    assert(bst_find(b, &(tab[i])));
  /*              5
   *          ---   ---
   *        2            7
   *     --  --       --  --
   *     0      3     6     9
   *   -- --  -- --       -- --  
   *  -1   1      4       8   10
   */

  for (int i = 0; i < n; i++) {
    bst_rm(b, &(tab[i]));
    assert(!bst_find(b, &(tab[i])));
    
    for (int j = i + 1; j < n; j++)
      assert(bst_find(b, &(tab[j])));

    assert(bst_size(b) == n - i - 1);
  }
  
  bst_free(b);
}


int main(int argc, char *argv[]) {

  printf("bst test \n");

  bst_test_new();
  bst_test_add();
  bst_rm_test();
  
  return 0;
}
