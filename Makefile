CC = cc
CFLAGS+=-std=c99 -Wall -g -O0


test: stack_test memory_test
	@echo ""
	@./stack_test
	@./memory_test

%.o: src/%.c
	$(CC) $(CFLAGS) -c $^

stack_test: test/stack_test.c stack.o
memory_test: test/memory_test.c memory.o stack.o
bintree_test: test/bintree_test.c bintree.o memory.o stack.o
%_test:
	$(CC) $(CFLAGS) $^ -o $@

clean:
	@rm -vrf *.o *~ *\#
	@rm -vf *_test
	@rm -vrf *.dSYM
