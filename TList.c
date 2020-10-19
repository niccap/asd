/*
 * TList: lista ordinata
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "TList.h"

/* operazioni sui nodi */

TNode *nodeCreate(TInfo info) {
    TNode *new = malloc (sizeof(TNode));
    if (new != NULL) {
        new->info = info;
        new->link = NULL;
    }
    return new;
}

void nodeDestroy(TNode *node) {
    free (node);
}

/* operazioni sulle liste */

TList listCreate() {
    return NULL;
}

TList listDestroy(TList list) {
    TNode *node;
    while (list != NULL) {
        node = list;
        list = list->link;
        nodeDestroy(node);
    }
    return list;
}

void listPrint(TList list) {
    if (list != NULL) {
        infoPrint (list->info);
        listPrint (list->link);
    }
    else 
        printf ("\n");
}

TNode *listSearch(TList list, TInfo info) {
    if (list == NULL || infoGreater(list->info, info)) 
        return NULL;
    if (infoEqual(list->info, info))
        return list;
    return listSearch(list->link, info);
}

TList listInsert(TList l, TInfo info) {
    if (l == NULL || infoGreater(l->info, info)) {
        TNode *node = nodeCreate(info);
        assert (node != NULL);
        node->link = l;
        return node;
    }
    l->link = listInsert(l->link, info);
    return l;
}

TList listDelete(TList l, TInfo info) {
    if (l == NULL || infoGreater(l->info, info)) 
        return l;
    if (infoEqual(l->info, info)) {
        TList m = l->link;
        nodeDestroy(l);
        return m;
    }
    l->link = listDelete(l->link, info);
    return l;
}