#include <stdio.h>
#include <stdlib.h>
#include "structs/cell/cell.hpp"
#include "structs/maze/maze.hpp"

int main(){

    maze *maze_=(maze*)malloc(sizeof(maze));
    char fileName[20]="maze.txt";
    initMaze(maze_, fileName);
    backtrackingAlghoritmMaze(maze_);

}   