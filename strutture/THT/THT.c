/*
 * THT: hash table a indirizzamento chiuso
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "THT.h"
#include "TInfo.h"

THT *HTcreate (int n) {
    THT *ht = malloc (sizeof(THT));
    assert (ht != NULL);
    
    ht->bucket = malloc (n * sizeof(TList));
    assert (ht->bucket != NULL);
    
    for (int i=0; i<n; i++)
        ht->bucket[i] = listCreate();
    ht->n_bucket = n;
    return ht;
}

void HTdestroy (THT* ht) {
    for (int i=0; i<ht->n_bucket; i++)
        ht->bucket[i] = listDestroy(ht->bucket[i]);
    free (ht->bucket);
    free (ht);
}

TValue *HTsearch (THT* ht, TKey key) {
    unsigned h = keyHash(key) % ht->n_bucket;
    TInfo info = {key};
    TNode* node = listSearch(ht->bucket[h], info);
    if (node != NULL) 
        return &node->info.value;
    return NULL;
}

void HTinsert (THT* ht, TKey key, TValue value) {
    unsigned h = keyHash(key) % ht->n_bucket;
    TInfo info = {key, value};
    TNode* node = listSearch(ht->bucket[h], info);
    if (node != NULL)
        node->info.value = value;
    else
        ht->bucket[h] = listInsert(ht->bucket[h], info);
}

void HTdelete (THT* ht, TKey key) {
    unsigned h = keyHash(key) % ht->n_bucket;
    TInfo info = {key};
    ht->bucket[h] = listDelete(ht->bucket[h], info);
}

void HTprint(THT* ht) {
    for (int i = 0; i < ht->n_bucket; i++)
        for (TNode *node = ht->bucket[i]; node != NULL; node = node->link)
            infoPrint(node->info);
}

void HTprintStructure (THT* ht) {
    for (int i = 0; i < ht->n_bucket; i++) {
        printf ("Bucket %2d -> ", i);
        for (TNode *node = ht->bucket[i]; node != NULL; node = node->link)
            infoPrint(node->info);
        printf ("\n");
    }
}