CC = cc
CFLAGS := -std=c99 -Wall

CFILE = $(wildcard ../src/*.c ../example/*.c)
OBJ  := $(patsubst ../src/%.c, %.o, $(CFILE))
OBJ  := $(patsubst ../example/%.c, %.o, $(OBJ))

TEST = $(wildcard ../test/*.c)
EXEC = $(patsubst ../test/%_test.c, %_test, $(TEST))


%.o:
	$(CC) $(CFLAGS) -c $(CFILE)

%_test:
	$(CC) $(CFLAGS) -o $@ ../test/$@.c $(OBJ)


all: $(OBJ) $(EXEC)
	@echo "compile all done"
	@echo ""

test: all
	@./stack_test
	@./pool_test
	@./bintree_test
	@./bst_test

clean:
	@rm -vf $(OBJ)
	@rm -vf $(EXEC)
	@rm -vrf *.dSYM


.PHONY: test clean
