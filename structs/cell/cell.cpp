#include "cell.hpp"

void initCell(cell *cell, typeCell typeCell){
    cell->_typeCell=typeCell;
    cell->pathUsed=0;
}
void setPathUsedCell(cell *cell, int pathUsed){
    cell->pathUsed=pathUsed;
}
typeCell getTypeCellCell(cell *cell){
    return cell->_typeCell;
}
int getPathUsedCell(cell *cell){
    return cell->pathUsed;
}