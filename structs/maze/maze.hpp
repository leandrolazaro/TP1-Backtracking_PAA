#ifndef MAZE_H
#define MAZE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <string.h>
#include "../cell/cell.hpp"
#include "../stack/stack.hpp"
#include "../row/row.hpp"

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
void mazeShowMaze(cell ***_cell, int sizeX, int sizeY);
void mazeDeleteMaze(maze *_maze);
#ifdef DEBUG
    int mazeMoveStudent(maze *_maze, int backtrackingCoordinateY, int backtrackingCoordinateX, int *sucessCoordinateY, int *sucessCoordinateX, int *movements, int *recursiveCalls, stack ** exitRoute);
#endif
#ifndef DEBUG
    int mazeMoveStudent(maze *_maze, int backtrackingCoordinateY, int backtrackingCoordinateX, int *sucessCoordinateY, int *sucessCoordinateX, int *movements, stack ** exitRoute);
#endif
void mazeInitRandomMaze(maze *_maze, int dificult);
void mazeWidthSearch(maze* _maze);
row* mazeWidthSearchAlghoritm(maze* _maze, row* _row);


#endif