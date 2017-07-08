#ifndef _BST_H_
#define _BST_H_

#include "bintree.h"
#include "../config.h"

typedef struct bst {
  size_t size;
  int (*lt_func)(const void *data1, const void *data2);
  bintree *bt;
} bst;


// sizeof_content == 0 || init_size == 0 => NULL 
bst *bst_new(const size_t sizeof_content,
	     const size_t init_size,
	     int (*lt_func)(const void *data1, const void *data2));

size_t bst_size(const bst *b);


int bst_find(const bst *b, const void *data);

void *bst_add(bst *b, const void *data);

void bst_rm(bst *b, const void *data);

void bst_free(bst *b);


#endif //_BST_H_
