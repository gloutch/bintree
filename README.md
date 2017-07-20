# bintree

It's a first implementation of polymorphic binary tree in C.

As example bintree.h was used to make generic [Binary search tree](https://en.wikipedia.org/wiki/Binary_search_tree), and then a specific **integer binary search tree**.

`make all` compiles all sources,  `make clean` deletes all binaries.



### Usage

Binary tree

```C
#include "src/bintree.h"

bintree *bt = bt_new(sizeof(int), 
                     8 /* initial non zero size */,
                     1 /* enable garbage collector */);

node *n = bt_node(bt);     		/* create node */
*(int *) node_data(n) = 4; 		/* give you a ptr to store data */
bt_newr(bt_root(bt), n);   		/* add it at the empty tree */

bt_free(bt);
```

Integer binary search tree

```C
#include "example/ibst.h"

bst *tree = ibst_new(8 /* initial non zero size */);

ibst_add(tree, 3);
ibst_add(tree, -2);
ibst_rm(tree, 3);

if (ibst_find(tree, -2)) {
  // do something
}

ibst_free(tree)
```





### About memory

The core issue is to limit calls to `malloc` to create each node.

#### Stack

A classic stack that extends its memory by realloc.

For a [constant amortized analysis](https://en.wikipedia.org/wiki/Amortized_analysis#Dynamic_Array) it doubles its size when the stack is full.

#### Pool

A malloced pool manager.

- `pool_empty(sizeof_content, init_size)` mallocs a pool of `init_size` elements and stores all free pointers in a stack. 

- `pool_collector(pool, free_func)` enables **~garbage collector** using `free_func` (that had to use `pool_remove`).

- `pool_slot(pool)`  provides pointer to a `sizeof_content` free area. 

  If the pool is full:

  1. if there is a garbage collector function, it will call it on every elements to find a free slot.

  2. else, it mallocs a new area and double its size.

​        Again, **constant amortized analysis**.

- `pool_remove(pool, ptr)` explicitly free this element

  ​



### Bintree

Provide basic tree functions. Trees are like [Directed acyclic graph](https://en.wikipedia.org/wiki/Directed_acyclic_graph) in order to share node between branches. Therefore nodes can have several parents.

- `bt_new(sizeof_content, init_size, bool)` create a binary tree. `bool` is a way to chose garbage collector on your nodes (for instance it's useless in bst.c).

- `bt_root(bt)` return `nil` node if the tree is empty, otherwise the root.

  To create a root use `bt_newr(bt_root(bt), root)` and don't touch much the `nil` node ;)

- `bt_nil(bt)` return the `nil` node of the binary tree.

- `bt_root_nil(bt)` remove the root of the `bt` tree.

  Root doesn't have parent so there is a specific function to delete the root.

  ​

- `bt_node(bt)` return a whole new node using `pool_slot`.

- `bt_newr(parent, right)` place `right` as the right child of `parent` (`right` can be `bt_nil(bt)`)

- `bt_newl(parent, left)` similar to above.

  ​

- `node_right(node)` return the right child of `node`

- `node_left(node)` a bit like above

- `node_data(node)` return pointer to area to store data.

- `node_parent(node)`  don't have too much sens in a directed acyclic graph, but return the **latest parent**  assigned of `node`, which is useful in classic tree like bst.

  ​

- `bt_node_free(bt, node)` must be use to explicitly remove a node from memory

- `bt_free(bt)` free the whole tree ans nodes

  ​


### Test

`make test` executes all test.

All executables were checked by [valgrind](http://valgrind.org/) and remained without leak memory so far.