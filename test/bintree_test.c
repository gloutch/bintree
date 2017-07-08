#include <stdio.h>
#include <assert.h>

#include "../src/bintree.h"

#define BOOL_GC 1


void bintree_empty_test() {
  printf("\t bintree_empty \n");
  
  bintree *a = bt_new(0, 1, BOOL_GC);
  assert(a == NULL);

  bintree *b = bt_new(1, 0, BOOL_GC);
  assert(b == NULL);

  bintree *bt = bt_new(1, 1, BOOL_GC);
  assert(bt != NULL);
  assert(bt_root(bt) == bt_nil(bt));
  assert(node_parent(bt_root(bt)) == bt_nil(bt));
  
  bt_free(bt);
}

void bintree_add_test() {
  printf("\t bintree_add \n");

  bintree *bt = bt_new(sizeof(char), 1, BOOL_GC);
  /*  nil
   */

  assert(bt_root(bt) == bt_nil(bt));

  node *n1 = bt_node(bt);
  bt_newl(bt_root(bt), n1);
  *(char *) node_data(n1) = 'a';
  /*   n1:'a'
   */
  
  assert(bt_root(bt) == n1);
  assert(node_parent(n1) == bt_nil(bt));
  assert(*(char *) node_data(bt_root(bt)) == 'a');

  node *n2 = bt_node(bt);
  bt_newl(n1, n2);
  *(char *) node_data(n2) = 'b';
  /*       n1:'a'
   *      /
   *     /
   *  n2:'b'
   */
 
  assert(node_left(n1) == n2);
  assert(node_parent(n2) == n1);
  assert(*(char *) node_data(node_left(bt_root(bt))) == 'b');

  node *n3 = bt_node(bt);
  bt_newr(n1, n3);
  *(char *) node_data(n3) = 'c';
  /*       n1:'a'
   *      /    \
   *     /      \
   *  n2:'b'   n3:'c'
   */

  assert(node_right(n1) == n3);
  assert(node_parent(n3) == n1);
  assert(node_right(node_right(n1)) == bt_nil(bt));
  assert(*(char *) node_data(node_right(bt_root(bt))) == 'c');
  
  bt_free(bt);
}

void bintree_rm_test() {
  printf("\t bintree_rm \n");

  bintree *bt = bt_new(sizeof(char), 1, BOOL_GC);

  node *n1 = bt_node(bt);
  *(char *) node_data(n1) = 'a';
  bt_newl(bt_root(bt), n1);

  node *n2 = bt_node(bt);
  *(char *) node_data(n2) = 'b';
  bt_newl(n1, n2);

  node *n3 = bt_node(bt);
  *(char *) node_data(n3) = 'c';
  bt_newr(n1, n3);
  
  /*       n1:'a'
   *      /    \
   *     /      \
   *  n2:'b'   n3:'c'
   */
  
  bt_newl(n1, bt_nil(bt));
  assert( node_left(n1)  == bt_nil(bt));
  assert( node_right(n1) != bt_nil(bt));
  assert( node_right(n1) == n3);

  bt_newr(n1, bt_nil(bt));
  assert(node_right(n1) == bt_nil(bt));

  bt_root_nil(bt);
  assert(bt_root(bt) == bt_nil(bt));
  
  bt_free(bt);
}



int main(int argc, char *argv[]) {

  printf("bintree_test \n");
  bintree_empty_test();
  bintree_add_test();
  bintree_rm_test();
  
  return 0;
}
