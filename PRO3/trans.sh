#!/bin/sh

./ex1/source/ProbGen
./ex1/source/OBSTree 1
dot -Tpng ./ex1/output/size1/graph.dot -o ./ex1/output/size1/OBSTree.png
./ex1/source/OBSTree 2
dot -Tpng ./ex1/output/size2/graph.dot -o ./ex1/output/size2/OBSTree.png
./ex1/source/OBSTree 3
dot -Tpng ./ex1/output/size3/graph.dot -o ./ex1/output/size3/OBSTree.png
./ex1/source/OBSTree 4
dot -Tpng ./ex1/output/size4/graph.dot -o ./ex1/output/size4/OBSTree.png
./ex1/source/OBSTree 5
dot -Tpng ./ex1/output/size5/graph.dot -o ./ex1/output/size5/OBSTree.png
./ex1/source/OBSTree 6
dot -Tpng ./ex1/output/size6/graph.dot -o ./ex1/output/size6/OBSTree.png

./ex2/source/StrGen
./ex2/source/LCS 1
./ex2/source/LCS 2
