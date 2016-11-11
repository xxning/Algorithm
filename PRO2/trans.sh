#!/bin/sh
./source/RB_Tree 20
dot -Tpng ./output/size20/graph.dot -o ./output/size20/size20.png
./source/RB_Tree 40
dot -Tpng ./output/size40/graph.dot -o ./output/size40/size40.png
./source/RB_Tree 60
dot -Tpng ./output/size60/graph.dot -o ./output/size60/size60.png
./source/RB_Tree 80
dot -Tpng ./output/size80/graph.dot -o ./output/size80/size80.png
./source/RB_Tree 100
dot -Tpng ./output/size100/graph.dot -o ./output/size100/size100.png
