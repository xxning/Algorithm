CC=g++
CFLAGS=-I include

all: source/RB_Tree

source/RB_tree:	source/RB_Tree.cc
	$(CC) -o $@ $<


.PHONEY:clean
clean:
	rm -f */*/*~ */*~ *~
	rm -f output/*/*
	rm -f source/RB_Tree
