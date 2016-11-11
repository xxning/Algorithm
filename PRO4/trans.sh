#!/bin/sh

./ex1/source/EdgeGen 
./ex1/source/SCC 1
dot -Tpng ./ex1/output/size1/graph.dot -o ./ex1/output/size1/SCC.png
./ex1/source/SCC 2
dot -Tpng ./ex1/output/size2/graph.dot -o ./ex1/output/size2/SCC.png
./ex1/source/SCC 3
dot -Tpng ./ex1/output/size3/graph.dot -o ./ex1/output/size3/SCC.png
./ex1/source/SCC 4
#dot -Tpng ./ex1/output/size4/graph.dot -o ./ex1/output/size4/SCC.png
./ex1/source/SCC 5
#dot -Tpng ./ex1/output/size5/graph.dot -o ./ex1/output/size5/SCC.png
./ex1/source/SCC 6
#dot -Tpng ./ex1/output/size6/graph.dot -o ./ex1/output/size6/SCC.png

./ex2/source/EdgeGen 
./ex2/source/Johnson 1
dot -Tpng ./ex2/output/size1/graph.dot -o ./ex2/output/size1/Graph.png
./ex2/source/Johnson 2
dot -Tpng ./ex2/output/size2/graph.dot -o ./ex2/output/size2/Graph.png
./ex2/source/Johnson 3
dot -Tpng ./ex2/output/size3/graph.dot -o ./ex2/output/size3/Graph.png
./ex2/source/Johnson 4
#dot -Tpng ./ex2/output/size4/graph.dot -o ./ex2/output/size4/Graph.png
./ex2/source/Johnson 5
#dot -Tpng ./ex2/output/size5/graph.dot -o ./ex2/output/size5/Graph.png
./ex2/source/Johnson 6
#dot -Tpng ./ex2/output/size6/graph.dot -o ./ex2/output/size6/Graph.png
