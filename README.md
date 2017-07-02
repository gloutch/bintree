# bintree

It's a first implementation of polymorphic binary tree in C.

Run `make` to compile and test the whole project.



### implementation

The core issue is about memory management like extend memory as needed

- `stack.c` is a classic stack that extends its memory by realloc.

  For a constant amortized complexity it doubles its size when the stack is full.

- `pool.c` is a somewhat redo of malloc.

  The main goal is to manage an allocated pool for many objects and avoid leaks memory. 

  It mallocs a pool and stores the pointers of all free elements in it. Then it provides those pointer as needed. Again it double its size but using malloc this time in order to keep valide pointers that are using. Storing each malloced pool pointers in a stack.

  Enable a ~garbage collector

- `bintree.c` try to provide basic tree functions.

  Tree must be as a Directed Acyclic Graph.

### test

`make test` launch test.

All executables were checked by [valgrind](http://valgrind.org) and remained without leak memory so far.



### TODO

1. Example of Binary Search Tree
2. Example int Binary Search Tree
3. Maybe kd-tree too