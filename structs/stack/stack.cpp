#include "stdlib.h"
#include "stack.hpp"

bool stackInitStack(stack ** node){
    (*node) = NULL;
    return true;
}

bool stackDestroyStack(stack ** node) {
    if((*node)==NULL) {
        return false;
    }

    if(((**node).next)==NULL) {
        free(*node);
        (*node) = NULL;
        return true;
    }

    return stackDestroyStack(&((**node).next));
}

bool stackCreateNode(stack ** node, int X, int Y) {
    stackDestroyStack(node);
    (*node) = (stack*)malloc(sizeof(stack));
    if((*node)==NULL) {
        return false;
    }

    (**node).X=X;
    (**node).Y=Y;
    (**node).next = NULL;
    return true;
}

bool stackStack(stack ** node, int X, int Y) {
    if((*node)==NULL) {
        stackCreateNode(node, X, Y);
        return true;
    }

    return stackStack(&((**node).next),X,Y);
}

bool stackUnstack(stack ** node, int * X, int * Y) {
    if((*node)==NULL) {
        return false;
    }

    if(((**node).next)==NULL) {
        (*X) = (**node).X;
        (*Y) = (**node).Y;
        free(*node);
        (*node) = NULL;
        return true;
    }

    return stackUnstack(&((**node).next), X, Y);
}