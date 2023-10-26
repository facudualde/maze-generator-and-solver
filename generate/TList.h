#pragma once
#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    int x;
    int y;
} Tuple;

typedef struct _TNode
{
    Tuple data;
    struct _TNode *next;
} TNode;
typedef TNode* TList;

TList tlist_create();

void tlist_delete(TList list);

void tlist_add_to_the_end(TNode **list, unsigned int x, unsigned int y);

void tlist_print(TList list);