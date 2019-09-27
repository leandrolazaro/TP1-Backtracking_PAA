#include <stdio.h>
#include <stdlib.h>
#include "structs/cell/cell.hpp"
#include "structs/maze/maze.hpp"
#include "structs/stack/stack.hpp"

int main(){

    maze * maze_=(maze*)malloc(sizeof(maze));
    stack * exitRoute;
    int x, y;
    char fileName[20]="maze.txt";
    mazeInitMaze(maze_, fileName);
    mazeBacktrackingAlghoritmMaze(maze_, &exitRoute);

    while (exitRoute!=NULL)
    {
        stackUnstack(&exitRoute, &x, &y);
        printf("%d %d\n", x, y);
    }
    



}   