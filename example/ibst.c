#include "ibst.h"


static int intcmp(const void *int1, const void *int2) {
  return (*(int *) int1) - (*(int *) int2);
}


bst *ibst_new(size_t size) {
  return bst_new(sizeof(int), size, intcmp);
}

size_t ibst_size(const bst *b) {
  return bst_size(b);
}

int ibst_find(const bst *b, const int i) {
  return bst_find(b, &i);
}

void ibst_add(bst *b, const int i) {
  *(int *) bst_add(b, &i) = i;
}

void ibst_rm(bst *b, const int i) {
  bst_rm(b, &i);
}

int ibst_min(const bst *b) {
  node *n = bt_root(b->bt);
  node *nil = bt_nil(b->bt);
  
  while (node_left(n) != nil)
    n = node_left(n);

  return *(int *) node_data(n);
}


int ibst_max(const bst *b) {
  node *n = bt_root(b->bt);
  node *nil = bt_nil(b->bt);
  
  while (node_right(n) != nil)
    n = node_right(n);

  return *(int *) node_data(n);
}



void ibst_free(bst *b) {
  bst_free(b);
}
