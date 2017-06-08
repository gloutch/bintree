# bintree

It's a first implementation of polymorphic binary tree in C.



### compiling

run `make` to compile and test the whole repository.



### files

- `stack.c` is a classic stack and manage extending memory.  

- `memory.c` is a redo of `malloc` basicly.

  Its aim is to manage memory to avoid leaks, then have a more friendly usage than `malloc` and `free`.

- `bintree.c` is to manage binary tree with nil node on each ends.




### test

`make test` launch test.
