#ifndef STACK_H
#define STACK_H
typedef struct stack {
    int X;
    int Y;
    struct stack * next;
} stack;

bool stackInitStack(stack ** node);
bool stackCreateNode(stack ** node, int X, int Y);
bool stackStack(stack ** node, int X, int Y);
bool stackUnstack(stack ** node, int * X, int * Y);
#endif