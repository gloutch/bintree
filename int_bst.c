#include "int_bst.h"


/* return node with i data if it exists,
 * nil node otherwise
 */
static node *search(const bintree *bst, int i) {
  
  node *n = bt_root(bst);
  int *data;
  
  while ( !node_is_nil(n) ) {
    
    data = node_data(n);
    if (*data < i)
      n = node_left(n);
    else if(*data > i)
      n = node_right(n);
    else
      return n;
  }
  return n;
}


bintree *ibst_empty(const size_t init_size) {  
  return bt_empty(sizeof(int), init_size);
}

size_t ibst_size(const bintree *bt) {
  return bt_size(bt);
}

int ibst_add(bintree *bst, const int i) {

  node *n = bt_root(bst);
  int *data;
  
  while ( !node_is_nil(n) ) {

    data = node_data(n);
    if (*data < i) {
      if (node_is_nil(node_left(n))) {
	data = node_data(bt_addl(bst, n));
	*data = i;
      } else 	
	n = node_left(n);

    } else if(*data > i)  
      if (node_is_nil(node_right(n))) {
	data = node_data(bt_addr(bst, n));
	*data = i;
      } else
	n = node_right(n);
    
    else
      return 0;
  }
  return 0;
}



static int extract_max(bintree *bst, node *n) {
  while ( !node_is_nil(node_right(n)) )
    n = node_right(n);

  int *data = node_data(n);
  bt_replace_left(bst, n, node_left(n));
  return *data;
}

static void remove_node(bintree *bst, node *n) {
  if (node_is_nil(node_left(n)))
    bt_replace_right(bst, n, node_right(n));
  else {
    int *data = node_data(n);
    *data = extract_max(bst, node_left(n));
  }
}

int ibst_rm(bintree *bst, const int i) {
  node *n = search(bst, i);
  if (!node_is_nil(n)) {
    remove_node(bst, n);
    return 1;
  }
  return 0;
}


int ibst_search(const bintree *bst, const int i) {
  return node_is_nil(search(bst, i));
}

void ibst_free(bintree *bst) {
  bt_free(bst);
}
