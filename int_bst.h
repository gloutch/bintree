#ifndef _INT_BST_H_
#define _INT_BST_H_

#include "bintree.h"

/* BST
 */


// (init_size == 0)  =>  NULL
bintree *ibst_empty(const size_t init_size);

size_t ibst_size(const bintree *bt);

int ibst_add(bintree *bst, const int i);

int ibst_rm(bintree *bst, const int i);

int ibst_search(const bintree *bst, const int i);

void ibst_free(bintree *bst);


#endif //_INT_BST_H_
