#ifndef ROW_H
#define ROW_H
#include "../stack/stack.hpp"
#include "stdlib.h"
#include <stdio.h>

typedef struct row {
    int X;
    int Y;
    int keysQuantity;
    struct row * previous;
    struct row * next;
} row;

void rowInitRow(row** _row, int Y, int X, int keysQuantity);
void rowInsertNode(row *_row, int Y, int X, int keysQuantity);
row* rowSearchNode(row *_row, int Y, int X);
void rowDeleteRow(row *_row);
void rowDeleteRowPrevious(row *_row);
void rowDeleteRowNext(row *_row);
row* rowSearchLastNode(row*_row);
void rowShowAllPreviousNode(row*_row);

#endif