#include "bintree.h"


struct node {
  struct node *parent;
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
  
  bt->nil.parent = &(bt->nil);
  bt->nil.right  = &(bt->nil);
  bt->nil.left   = &(bt->nil);
  // store each element as {node, content}
  bt->node_memo = memo_empty(sizeof(struct node) + sizeof_content, init_size);
  
  return bt;
}


size_t bt_size(const bintree *bt) {
  return memo_nb_elem(bt->node_memo);
}

node *bt_root(const bintree *bt) {
  if (bt->nil.right == &(bt->nil))
    return bt->nil.left;
  else
    return bt->nil.right;
}

node *bt_addl(bintree *bt, node *n) {

  node *new = memo_new_ptr(bt->node_memo);
  // init new node
  new->parent = n;
  new->right  = &(bt->nil);
  new->left   = &(bt->nil);
  // connect the parent
  n->left = new;
  return new;
}

node *bt_addr(bintree *bt, node *n) {

  node *new = memo_new_ptr(bt->node_memo);
  
  new->parent = n;
  new->right  = &(bt->nil);
  new->left   = &(bt->nil);
  
  n->right = new;
  return new;
}

void bt_remove(bintree *bt, node *n) {
  if (n->parent->left == n)
    n->parent->left = &(bt->nil);
  else
    n->parent->right = &(bt->nil);

  memo_remove(bt->node_memo, n);
}


/* #define NODE_GETTER(name) \ */
/*   node *node_ ## name(node *n, int step) { \ */
/*   int i = 0; \ */
/*   while ((i < step) || !node_is_nil(n)) { \ */
/*     i++; \ */
/*     n = n-> ## name; \ */
/*   } \ */
/*   return n; \ */
/* } \ */
  
node *node_parent(const int step, node *n) {
  int i = 0;
  while ((i < step) && !node_is_nil(n)) {
    i++;
    n = n->parent;
  }
  return n;
}

node *node_right(const int step, node *n) {
  int i = 0;
  while ((i < step) && !node_is_nil(n)) {
    i++;
    n = n->right;
  }
  return n;
}

node *node_left(const int step, node *n) {
  int i = 0;
  while ((i < step) && !node_is_nil(n)) {
    i++;
    n = n->left;
  }
  return n;
}

// node_memo store each node like [node, content]
// data is juste after the node
void *node_data(node *n) {
  return (n + 1);
}

int node_is_nil(const node *n) {
  return (n == n->parent);
}


void bt_free(bintree *bt) {
  memo_free(bt->node_memo);
  free(bt);
}
