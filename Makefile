CC = cc
CFLAGS+=-std=c99 -Wall


test: stack_test pool_test bintree_test bst_test
	@echo ""
	@./stack_test
	@./pool_test
	@./bintree_test
	@./bst_test

%.o: src/%.c
	$(CC) $(CFLAGS) -c $^

stack_test: test/stack_test.c stack.o
pool_test: test/pool_test.c pool.o stack.o
bintree_test: test/bintree_test.c bintree.o pool.o stack.o
bst_test: test/bst_test.c bst.o bintree.o pool.o stack.o
%_test:
	$(CC) $(CFLAGS) $^ -o $@

clean:
	@rm -vrf *.o *~ *\#
	@rm -vf *_test
	@rm -vrf *.dSYM
