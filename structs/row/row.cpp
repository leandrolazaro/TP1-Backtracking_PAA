#include "row.hpp"
#include "../stack/stack.hpp"

void rowInitRow(row** _row, int Y, int X, int keysQuantity){
    *_row=(row*)malloc(sizeof(row));
    (*_row)->Y=Y;
    (*_row)->X=X;
    (*_row)->previous=NULL;
    (*_row)->next=NULL;
    (*_row)->keysQuantity=keysQuantity;
}

void rowInsertNode(row *_row, int Y, int X, int keysQuantity){
    row* _lastRow=rowSearchLastNode(_row);
    _lastRow->next=(row*)malloc(sizeof(row));
    _lastRow->next->Y=Y;
    _lastRow->next->X=X;
    _lastRow->next->previous=_row;
    _lastRow->next->next=NULL;
    _lastRow->next->keysQuantity=keysQuantity;
}

row* rowSearchNode(row *_row, int Y, int X){
    if(_row->next==NULL){
        return NULL;
    }
    if(_row->X==X && _row->Y==Y){
        return _row;
    }
    return rowSearchNode(_row->next, Y, X);
}

void rowDeleteRow(row *_row){
    rowDeleteRowPrevious(_row);
    rowDeleteRowNext(_row);
}

void rowDeleteRowPrevious(row *_row){
    if(_row!=NULL){
        rowDeleteRowPrevious(_row->previous);
        delete(_row);
    }
    return;
}

void rowDeleteRowNext(row *_row){
    if(_row!=NULL){
        rowDeleteRowNext(_row->next);
        delete(_row);
    }
    return;
}

row* rowSearchLastNode(row*_row){
    if(_row->next==NULL){
        return _row;
    }
    return rowSearchLastNode(_row->next);
}

void rowShowAllPreviousNode(row*_row){
    int x=0;
    int y=0;
    stack* _stack=NULL;
    stackInitStack(&(_stack));
    while (_row!=NULL){
        stackStack((&_stack), _row->X, _row->Y);
        _row=_row->previous;
    }
    while (_stack!=NULL){
        stackUnstack(&_stack, &x, &y);
        printf("%d, %d\n", x, y);
    }
}
