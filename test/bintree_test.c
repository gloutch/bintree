#include <stdio.h>
#include <assert.h>

#include "../src/bintree.h"


void bintree_empty_test() {
  printf("\t bintree_empty_test \n");
  
  bintree *a = bt_empty(0, 1);
  assert(a == NULL);

  bintree *b = bt_empty(1, 0);
  assert(b == NULL);

  bintree *bt = bt_empty(1, 1);
  assert(bt != NULL);
  assert(bt_size(bt) == 0);
  assert(bt_root(bt) == bt_nil(bt));
  
  bt_free(bt);
}

void bintree_add_test() {
  printf("\t bintree_add_test \n");

  bintree *bt = bt_empty(sizeof(char), 1);
  /*  nil
   */

  assert(bt_root(bt) == bt_nil(bt));
  assert(bt_size(bt) == 0);

  node *n1 = bt_node(bt);
  bt_addl(bt_root(bt), n1);
  *(char *) node_data(n1) = 'a';
  /*   n1:'a'
   */
  
  assert(bt_root(bt) == n1);
  assert(*(char *) node_data(bt_root(bt)) == 'a');
  assert(bt_size(bt) == 1);

  node *n2 = bt_node(bt);
  bt_addl(n1, n2);
  *(char *) node_data(n2) = 'b';
  /*       n1:'a'
   *      /
   *     /
   *  n2:'b'
   */
 
  assert(node_left(n1) == n2);
  assert(*(char *) node_data(node_left(bt_root(bt))) == 'b');
  assert(bt_size(bt) == 2);

  node *n3 = bt_node(bt);
  bt_addr(n1, n3);
  *(char *) node_data(n3) = 'c';
  /*       n1:'a'
   *      /    \
   *     /      \
   *  n2:'b'   n3:'c'
   */

  assert(node_right(n1) == n3);
  assert(node_right(node_right(n1)) == bt_nil(bt));
  assert(*(char *) node_data(node_right(bt_root(bt))) == 'c');
  assert(bt_size(bt) == 3);
  
  bt_free(bt);
}

void bintree_rm_test() {
  printf("\t bintree_rm_test \n");

  bintree *bt = bt_empty(sizeof(char), 1);

  node *n1 = bt_node(bt);
  *(char *) node_data(n1) = 'a';
  bt_addl(bt_root(bt), n1);

  node *n2 = bt_node(bt);
  *(char *) node_data(n2) = 'b';
  bt_addl(n1, n2);

  node *n3 = bt_node(bt);
  *(char *) node_data(n3) = 'c';
  bt_addr(n1, n3);
  
  /*       n1:'a'
   *      /    \
   *     /      \
   *  n2:'b'   n3:'c'
   */

  // I need parent pointer un node!
  
  /* bt_remove(bt, n2); */
  /* assert( node_left(n1)  == bt_nil(bt)); */
  /* assert( node_right(n1) != bt_nil(bt)); */
  /* assert(bt_size(bt) == 2); */

  /* bt_remove(bt, n3); */
  /* assert(node_right(n1) == bt_nil(bt)); */
  /* assert(bt_size(bt) == 1); */

  /* bt_remove(bt, n1); */
  /* assert(bt_root(bt) == bt_nil(bt)); */
  /* assert(bt_size(bt) == 0); */
  
  bt_free(bt);
}



int main(int argc, char *argv[]) {

  printf("bintree_test \n");
  bintree_empty_test();
  bintree_add_test();
  bintree_rm_test();
  
  return 0;
}
