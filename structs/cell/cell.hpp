#ifndef CELL_H
#define CELL_H

#include <stdio.h>
#include <stdlib.h>

enum typeCell {student, empty, wall, door, key, output};

typedef struct cell{
    typeCell _typeCell;
    int pathUsed;
}cell;

void initCell(cell *cell, typeCell typeCell);
void setPathUsedCell(cell *cell, int pathUsed);
typeCell getTypeCellCell(cell *cell);
int getPathUsedCell(cell *cell);


#endif