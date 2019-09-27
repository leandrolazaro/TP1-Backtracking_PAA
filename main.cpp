#include <stdio.h>
#include <stdlib.h>
#include "structs/cell/cell.hpp"
#include "structs/maze/maze.hpp"
#include "structs/stack/stack.hpp"

int main(){

    #ifdef DEBUG
        printf("x-x-x-x-x-x-x DEBUG MODE x-x-x-x-x-x-x\n");
    #endif

    maze * maze_=(maze*)malloc(sizeof(maze));
    stack * exitRoute=NULL;
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