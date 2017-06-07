# bintree

This is a first implementation of polymorphic binary tree in C.



### compiling

run `make` to compile and test the whole repository.



### files

- `stack.c` is a classic stack and manage extending memory.  
- `memory.c` is a redo of malloc basicly. Its aim is to manage `malloc` and `free` to avoid leak memory and then have a more friendly usage.
- `bintree.c` is to manage binary tree with nil node on each end.




### test

`make test` launch test.

All test executions were check by [valgrind](http://valgrind.org), and remain without memory leaks. 