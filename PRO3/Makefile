CC=g++
CFLAGS=-I include

all: ex1/source/OBSTree ex1/source/ProbGen ex2/source/LCS ex2/source/StrGen
	

ex1/source/OBStree:	ex1/source/OBSTree.cc
	$(CC) -o $@ $<

ex1/source/ProbGen:	ex1/source/ProbGen.cc
	$(CC) -o $@ $<

ex2/source/LCS:		ex2/source/LCS.cc
	$(CC) -o $@ $<

ex2/source/StrGen:	ex2/source/StrGen.cc
	$(CC) -o $@ $<

.PHONEY:clean
clean:
	rm -f */*/*/*~  */*/*~ *~
	rm -f ex1/output/*/*
	rm -f ex2/output/*/*
	rm -f ex1/source/OBSTree ex1/source/ProbGen
	rm -f ex2/source/LCS ex2/source/StrGen
