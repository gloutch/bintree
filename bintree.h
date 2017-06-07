#ifndef _BIN_TREE_H_
#define _BIN_TREE_H_

#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "memory.h"


struct bintree;
typedef struct bintree bintree;

struct node;
typedef struct node node;

/** Binary Tree (manage memory)
 *
 * Don't manage memory error
 * Don't change to much the nil node
 */


// (sizeof_content == 0 || init_size == 0)  =>  NULL
bintree *bt_empty(const size_t sizeof_content, const size_t init_size);

// bintree *bt_merge(bintree *bt1, node *at, bintree *bt2);

size_t bt_size(const bintree *bt);


node *bt_root(const bintree *bt);

node *bt_addl(bintree *bt, node *n);

node *bt_addr(bintree *bt, node *n);

void bt_remove(bintree *bt, node *n);


// void node_swap(node *n1, node *n2);

node *node_parent(const int step, node *n);

node *node_right(const int step, node *n);

node *node_left(const int step, node *n);

void *node_data(node *n);

int node_is_nil(const node *n);


void bt_free(bintree *bt);


#endif //_BIN_TREE_H_
