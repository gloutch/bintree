#ifndef _IBST_H_
#define _IBST_H_

#include "bst.h"


bst *ibst_new(size_t size);

size_t ibst_size(const bst *b);

int ibst_find(const bst *b, const int i);

void ibst_add(bst *b, const int i);

void ibst_rm(bst *b, const int i);

// if bst is empty, return random result
int ibst_min(const bst *b);

int ibst_max(const bst *b);


void ibst_free(bst *b);


#endif // _IBST_H_
