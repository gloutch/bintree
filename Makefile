
all:
	@$(MAKE) -sC build all

test:
	@$(MAKE) -sC build test

clean:
	@rm -vf src/*~  test/*~  example/*~
	@rm -vf src/*\# test/*\# example/*\#
	@$(MAKE) -sC build clean


.PHONY: clean test