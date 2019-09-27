#ifndef MAZE_H
#define MAZE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../cell/cell.hpp"

typedef struct maze{
    int sizeX;
    int sizeY;
    cell **_cell;
    int studentCoordinateX;
    int studentCoordinateY;
    int keysNumber;
}maze;

void initMaze(maze *_maze, char *fileName);
void backtrackingAlghoritmMaze(maze *_maze);
void mallocCellMaze(cell ***_cell, int sizeX, int sizeY);
int moveStudent(maze *_maze, int backtrackingCoordinateY, int backtrackingCoordinateX, int *sucessCoordinateY, int *sucessCoordinateX, int *movements);

#endif