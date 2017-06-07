#include <stdio.h>
#include <assert.h>

#include "bintree.h"


void bintree_empty_test() {
  printf("\t bintree_empty_test \n");
  
  bintree *a = bt_empty(0, 1);
  assert(a == NULL);

  bintree *b = bt_empty(1, 0);
  assert(b == NULL);

  bintree *bt = bt_empty(1, 1);
  assert(bt != NULL);
  assert(bt_size(bt) == 0);
  assert(node_is_nil(bt_root(bt)));
  
  bt_free(bt);
}

void bintree_add_test() {
  printf("\t bintree_add_test \n");

  bintree *bt = bt_empty(sizeof(char), 1);
  char *tmp;
  /*  nil
   */

  assert(node_is_nil(bt_root(bt)));
  assert(bt_size(bt) == 0);

  node *n1 = bt_addl(bt, bt_root(bt));
  tmp = node_data(n1);
  *tmp = 'a';
  /*    nil
   *     |
   *   n1:'a' <- root
   */
  
  assert(node_is_nil(node_parent(1, n1)));
  assert(bt_root(bt) == n1);
  tmp = node_data(bt_root(bt));
  assert(*tmp == 'a');
  assert(bt_size(bt) == 1);

  node *n2 = bt_addl(bt, n1);
  tmp = node_data(n2);
  *tmp = 'b';
  /*       nil
   *        |
   *       n1:'a'
   *      /
   *     /
   *  n2:'b'
   */
 
  assert(node_left(1, n1) == n2);
  assert(node_parent(1, n2) == n1);
  tmp = node_data(node_left(1, bt_root(bt)));
  assert(*tmp == 'b');
  assert(bt_size(bt) == 2);

  node *n3 = bt_addr(bt, n1);
  tmp = node_data(n3);
  *tmp = 'c';
  /*       nil
   *        |
   *       n1:'a'
   *      /    \
   *     /      \
   *  n2:'b'   n3:'c'
   */

  assert(node_parent(1, n3) == n1);
  assert(node_is_nil(node_parent(2, n3)));
  assert(node_right(1, n1) == n3);
  assert(node_is_nil(node_right(2, n1)));
  tmp = node_data(node_right(1, bt_root(bt)));
  assert(*tmp == 'c');
  assert(bt_size(bt) == 3);
  
  bt_free(bt);
}

void bintree_rm_test() {
  printf("\t bintree_rm_test \n");

  bintree *bt = bt_empty(sizeof(char), 1);
  char *tmp;

  node *n1 = bt_addl(bt, bt_root(bt));
  tmp = node_data(n1);
  *tmp = 'a';

  node *n2 = bt_addl(bt, n1);
  tmp = node_data(n2);
  *tmp = 'b';

  node *n3 = bt_addr(bt, n1);
  tmp = node_data(n3);
  *tmp = 'c';
  
  /*       nil
   *        |
   *       n1:'a'
   *      /    \
   *     /      \
   *  n2:'b'   n3:'c'
   */

  bt_remove(bt, n2);
  assert( node_is_nil(node_left( 1, n1)));
  assert(!node_is_nil(node_right(1, n1)));
  assert(bt_size(bt) == 2);

  bt_remove(bt, n3);
  assert(node_is_nil(node_right(1, n1)));
  assert(bt_size(bt) == 1);

  bt_remove(bt, n1);
  assert(node_is_nil(bt_root(bt)));
  assert(bt_size(bt) == 0);
  
  bt_free(bt);
}



int main(int argc, char *argv[]) {

  printf("bintree_test \n");
  bintree_empty_test();
  bintree_add_test();
  bintree_rm_test();
  
  return 0;
}
