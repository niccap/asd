/*
 * THT: hash table a indirizzamento chiuso
 */

#ifndef THT_H
#define THT_H
#include "TList.h"

typedef struct {
    TList *bucket;
    int n_bucket;
} THT;

THT *HTcreate (int n);
void HTdestroy (THT* ht);
void HTinsert (THT* ht, TKey key, TValue value);
void HTdelete (THT* ht, TKey key);
TValue *HTsearch (THT* ht, TKey key);
void HTprint(THT* ht);
void HTprintStructure(THT* ht);

#endif