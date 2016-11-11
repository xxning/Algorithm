CC=g++
CFLAGS=-I include

all: ex1/source/EdgeGen ex2/source/EdgeGen ex1/source/SCC ex2/source/Johnson
	

ex1/source/EdgeGen:	ex1/source/EdgeGen.cpp
	$(CC) -o $@ $<

ex1/source/SCC:	ex1/source/SCC.cpp

	$(CC) -o $@ $<

ex2/source/EdgeGen:	ex2/source/EdgeGen.cpp
	$(CC) -o $@ $<

ex2/source/Johnson:		ex2/source/Johnson.cpp
	$(CC) -o $@ $<


.PHONEY:clean
clean:
	rm -f */*/*/*~  */*/*~ *~
	rm -f ex1/output/*/* ex1/input/*/*
	rm -f ex2/output/*/* ex2/input/*/*
	rm -f ex1/source/EdgeGen ex1/source/SCC
	rm -f ex2/source/EdgeGen ex2/source/Johnson
