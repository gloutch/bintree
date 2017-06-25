#include "bintree.h"


struct node {
  int parent_counter;
  
  struct node *right;
  struct node *left;
};

struct bintree {
  struct node nil;
  struct memory *node_memo;
};


static void free_unreacheble(memory *memo, void *curr) {
  node *n = curr;
  if (n->parent_counter <= 0) {
    n->right->parent_counter -= 1;
    n->left->parent_counter -= 1;
    memo_remove(memo, n);
  }
}


bintree *bt_empty(const size_t sizeof_content, const size_t init_size, const int bool_garbage_collector) {

  if (sizeof_content == 0 || init_size == 0)
    return NULL;

  bintree *bt = malloc(sizeof(struct bintree));
  if (bt == NULL) {
    MALLOC_ERROR
    return NULL;
  }

  bt->nil.parent_counter = 0; // useless
  bt->nil.right  = &(bt->nil);
  bt->nil.left   = &(bt->nil);

  // store each element as {node, content}
  bt->node_memo = memo_empty(sizeof(struct node) + sizeof_content, init_size);
  if (bool_garbage_collector)
    memo_collector(bt->node_memo, free_unreacheble); 
  
  return bt;
}

node *bt_root(const bintree *bt) {
  if (bt->nil.right != &(bt->nil))
    return bt->nil.right;
  else
    return bt->nil.left;
}

node *bt_nil(bintree *bt) {
  return &(bt->nil);
}

void bt_root_nil(bintree *bt) {
  if (bt->nil.right != &(bt->nil)) {
    (bt->nil.right)->parent_counter -= 1;
    bt->nil.right = &(bt->nil);
    
  } else {
    (bt->nil.left)->parent_counter -= 1;
    bt->nil.left = &(bt->nil);
  }
}


node *bt_node(bintree *bt) {
  node *new = memo_slot(bt->node_memo);

  new->parent_counter = 0;
  new->right = &(bt->nil);
  new->left  = &(bt->nil);
  return new;
}

void bt_newl(node *parent, node *left) {
  parent->left->parent_counter -= 1;
  
  left->parent_counter += 1;
  parent->left = left;
}

void bt_newr(node *parent, node *right) {
  parent->right->parent_counter -= 1;

  right->parent_counter += 1;
  parent->right = right;
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



void bt_free_node(bintree *bt, node *n) {
  n->right->parent_counter -= 1;
  n->left->parent_counter -= 1;

  memo_remove(bt->node_memo, n);
}


void bt_free(bintree *bt) {
  memo_free(bt->node_memo);
  free(bt);
}
