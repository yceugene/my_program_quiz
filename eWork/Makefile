PWD := $(shell pwd)
SRC := BinaryTree wk01_test
INC := include
VPATH = $(SRC) $(INC)
vpath %.c $(SRC)
vpath %.h $(INC)

CC := gcc
FLAG := -I$(INC) -c

wk01Test_R: wk01Test_R.o
	$(CC) -o $@ $<

wk01Test_R.o: wk01Test_R.c 	ansWK01Test.h
	@$(CC) $(FLAG) $<

wk01Test_P: wk01Test_P.o
	$(CC) -o $@ $<

wk01Test_P.o: wk01Test_P.c 	ansWK01Test.h
	@$(CC) $(FLAG) $<

wk01Test: wk01Test.o
	$(CC) -o $@ $<

wk01Test.o: wk01Test.c 	ansWK01Test.h
	@$(CC) $(FLAG) $<

bTree: bTree.o
	@gcc -o $@ $<

bTree.o: bTree.c tree.h
	@$(CC) $(FLAG) $<
	@echo finished @ $(shell date)!

# .PHONY: clean
clean:
	rm -f *.o
	rm -f bTree
	rm -f wk01Test
	rm -f wk01Test_P
