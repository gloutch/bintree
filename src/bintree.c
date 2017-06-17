#include "bintree.h"


struct node {
  struct node *right;
  struct node *left;
};

struct bintree {
  struct node nil;
  struct memory *node_memo;
};


bintree *bt_empty(const size_t sizeof_content, const size_t init_size) {

  if (sizeof_content == 0 || init_size == 0)
    return NULL;

  bintree *bt = malloc(sizeof(struct bintree));
  if (bt == NULL) {
    MALLOC_ERROR
    return NULL;
  }
  
  bt->nil.right  = &(bt->nil);
  bt->nil.left   = &(bt->nil);
  // store each element as {node, content}
  bt->node_memo = memo_empty(sizeof(struct node) + sizeof_content, init_size);
  
  return bt;
}


size_t bt_size(const bintree *bt) {
  return memo_nb_elem(bt->node_memo);
}

const node *bt_nil(const bintree *bt) {
  return &(bt->nil);
}

node *bt_root(const bintree *bt) {
  if (bt->nil.right == &(bt->nil))
    return bt->nil.left;
  else
    return bt->nil.right;
}

node *bt_node(bintree *bt) {
  node *new = memo_new_ptr(bt->node_memo);

  new->right = &(bt->nil);
  new->left  = &(bt->nil);
  
  return new;
}


void bt_addl(node *parent, node *left) {
  parent->left = left;
}

void bt_addr(node *parent, node *right) {
  parent->right = right;
}

void bt_remove(const bintree *bt, node *n) {
  memo_remove(bt->node_memo, n);
}


node *node_right(const node *n) {
  return n->right;
}
node *node_left(const node *n) {
  return n->left;
}
// node_memo store each node like [node, content]
// data is juste after the node
void *node_data(const node *n) {
  return (void *) (n + 1);
}


void bt_free(bintree *bt) {
  memo_free(bt->node_memo);
  free(bt);
}
