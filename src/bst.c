#include "bst.h"

/* return node with i data if it exists,
 * nil node otherwise
 */
static node *search(const bst *b, const void *data) {

  node *nil = bt_nil(b->bt);
  node *n = bt_root(b->bt);
  
  while (n != nil) {
    
    int cmp = b->lt_func(data, node_data(n));
    if (cmp < 0)
      n = node_left(n);
    else if(cmp > 0)
      n = node_right(n);
    else
      return n;
  }
  return n;
}


bst *bst_new(const size_t sizeof_content,
	     const size_t init_size,
	     int (*lt_func)(const void *data1, const void *data2)) {

  if (sizeof_content == 0 || init_size == 0)
    return NULL;
  
  bst *b = malloc(sizeof(struct bst));
  if (b == NULL) {
    MALLOC_ERROR;
    return NULL;
  }
  b->size = 0;
  b->lt_func = lt_func;
  b->bt = bt_new(sizeof_content, init_size, 0 /* no garbage collector */);

  return b;
}

size_t bst_size(const bst *b) {
  return b->size;
}


int bst_find(const bst *b, const void *data) {
  return (search(b, data) != bt_nil(b->bt));
}


void *bst_add(bst *b, const void *data) {
  node *nil    = bt_nil(b->bt);
  node *n      = bt_root(b->bt);
  node *parent = node_parent(n);
  int cmp = 0; // initialize for valgrind, but don't matter
  
  while (n != nil) {
    cmp = b->lt_func(data, node_data(n));
    
    if (cmp < 0) {
      parent = n;
      n = node_left(n);
    } else if (cmp > 0) {
      parent = n;
      n = node_right(n);
    } else // data is already in n
      return node_data(n);
  }
  
  node *new = bt_node(b->bt);
  b->size += 1;
  if (cmp < 0)
    bt_newl(parent, new);
  else
    bt_newr(parent ,new);
  
  return node_data(new);
}


/*
 * extracte a substitute for target;
 *   min of tree rooted by node_right(target)
 *   or node_left(target)
 */
static node *substitute(bintree *bt, node *target) {
  node *nil = bt_nil(bt);
  
  if (node_right(target) != nil) {
    node *n = node_right(target);
    
    if (node_left(n) == nil) {
      bt_newl(n, node_left(target));
      return n;
    }
    // search the min, extract and place it
    n = node_left(n);
    while (node_left(n) != nil)
      n = node_left(n);
 
    bt_newl(node_parent(n), node_right(n));
    bt_newr(n, node_right(target));
    bt_newl(n, node_left(target));
    return n;
    
  } else
    return node_left(target);
}

void bst_rm(bst *b, const void *data) {
  node *nil = bt_nil(b->bt);
  node *target = search(b, data);

  if (target == nil)
    return; // *data isn't in the tree
  
  node *sub = substitute(b->bt, target);
  
  if (node_parent(target) == nil) {
    // target is the root
    bt_root_nil(b->bt);
    bt_newl(bt_root(b->bt), sub);
    
  } else {
    // target isn't the root
    node *parent = node_parent(target);
    if (node_right(parent) == target)
      bt_newr(parent, sub);
    else
      bt_newl(parent, sub);
  }
  b->size -= 1;
  bt_free_node(b->bt, target);
}


void bst_free(bst *b) {
  bt_free(b->bt);
  free(b);
}
