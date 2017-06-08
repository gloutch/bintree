CC = cc
CFLAGS+=-std=c99 -Wall


test: stack_test memory_test bintree_test int_bst.o
	@echo ""
	@./stack_test
	@./memory_test
	@./bintree_test

%.o: %.c
	$(CC) $(CFLAGS) -c $^

stack_test: stack_test.c stack.o
memory_test: memory_test.c memory.o stack.o
bintree_test: bintree_test.c bintree.o memory.o stack.o
%_test:
	$(CC) $(CFLAGS) $^ -o $@

clean:
	@rm -vf *.o *~ *\#
	@rm -vf *_test
	@rm -vrf *.dSYM
