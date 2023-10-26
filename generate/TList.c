#include "TList.h"

TList tlist_create()
{
    return NULL;
}

void tlist_delete(TList list)
{
    TNode *nodeToDelete;
    while(list != NULL)
    {
        nodeToDelete = list;
        list = list->next;
        free(nodeToDelete);
    }
}

void tlist_add_to_the_end(TNode **list, unsigned int x, unsigned int y)
{
    TNode *newTuple = malloc(sizeof(TNode));
    newTuple->data.x = x;
    newTuple->data.y = y;
    newTuple->next = NULL;
    if(*list == NULL)
        *list = newTuple;
    else
    {
        TNode *node = *list;
        for(; node->next != NULL; node = node->next);
        node->next = newTuple;
    }
}

void tlist_print(TList list)
{
    for(TNode *node = list; node != NULL; node = node->next)
        printf("(%d, %d)\n", node->data.x, node->data.y);
}