#ifndef _BIN_TREE_H_
#define _BIN_TREE_H_

#include <stdio.h>
#include <stdlib.h>

#include "../config.h"
#include "memory.h"


struct bintree;
typedef struct bintree bintree;

struct node;
typedef struct node node;

/** Binary Tree (manage memory)
 *   Don't manage memory error
 *   Don't touch too much the nil node
 */


// (sizeof_content == 0 || init_size == 0)  =>  NULL
bintree *bt_empty(const size_t sizeof_content, const size_t init_size, const int bool_garbage_collector);

node *bt_root(const bintree *bt);

node *bt_nil(bintree *bt);

void bt_root_nil(bintree *bt);


node *bt_node(bintree *bt);

void bt_newl(node *parent, node *left);

void bt_newr(node *parent,  node *right);


node *node_right(const node *n);

node *node_left(const node *n);

void *node_data(const node *n);


void bt_free_node(bintree *bt, node *n);

// void bt_free_all_nodes(bintree *bt);

void bt_free(bintree *bt);


#endif //_BIN_TREE_H_
