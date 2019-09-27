#ifndef MAZE_H
#define MAZE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../cell/cell.hpp"
#include "../stack/stack.hpp"

typedef struct maze{
    int sizeX;
    int sizeY;
    cell **_cell;
    int studentCoordinateX;
    int studentCoordinateY;
    int keysNumber;
}maze;

void mazeInitMaze(maze *_maze, char *fileName);
void mazeBacktrackingAlghoritmMaze(maze *_maze, stack ** exitRoute);
void mazeMallocCellMaze(cell ***_cell, int sizeX, int sizeY);
int mazeMoveStudent(maze *_maze, int backtrackingCoordinateY, int backtrackingCoordinateX, int *sucessCoordinateY, int *sucessCoordinateX, int *movements, stack ** exitRoute);

#endif