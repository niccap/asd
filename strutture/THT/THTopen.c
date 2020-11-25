/*
 * THTopen: hash table a indirizzamento aperto
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "THTopen.h"

THT *HTcreate (int n) {
    THT *ht = malloc (sizeof(THT));
    assert (ht != NULL);
    
    ht->bucket = malloc (n * sizeof(TInfo));
    ht->used = malloc (n * sizeof(int));
    assert (ht->bucket != NULL && ht->used != NULL);

    for (int i=0; i<n; i++)
        ht->used[i]=0;
    ht->n_bucket = n;
    ht->n_used = 0;
    return ht;
}

void HTdestroy (THT* ht) {
    free (ht->bucket);
    free (ht->used);
    free (ht);
}

void HTresize (THT* ht, int n) {
    TInfo *bucket = ht->bucket;
    int *used = ht->used;
    int n_bucket = ht->n_bucket;

    ht->bucket = malloc (n * sizeof(TInfo));
    ht->used = malloc (n * sizeof(int));
    assert (ht->bucket != NULL && ht->used != NULL);

    for (int i=0; i<n; i++)
        ht->used[i]=0;
    ht->n_bucket = n;
    ht->n_used = 0;
    
    for (int i = 0; i < n_bucket; i++)
        if (used[i])
            HTinsert(ht, bucket[i].key, bucket[i].value);

    free (bucket);
    free (used);
}

TValue *HTsearch (THT* ht, TKey key) {
    unsigned h = keyHash(key) % ht->n_bucket;
    TInfo info = {key};
    while (ht->used[h] && !infoEqual(info, ht->bucket[h])) 
        h = (h+1) % ht->n_bucket; 
    if (ht->used[h])
        return &ht->bucket[h].value;
    return NULL;
}

void HTinsert (THT* ht, TKey key, TValue value) {
    TValue *p = HTsearch(ht, key);
    if (p != NULL) { // aggiornamento valore associato alla chiave
        *p = value;
        return;
    }
    if (ht->n_used+1 >= ht->n_bucket*MAX_LOAD) // non c'è posto
        HTresize(ht, ht->n_bucket*GROW_FACTOR+1);
    
    unsigned h = keyHash(key) % ht->n_bucket;
    while (ht->used[h]) 
        h = (h+1) % ht->n_bucket; 
    ht->bucket[h].key = key;
    ht->bucket[h].value = value;
    ht->used[h] = 1;
    ht->n_used++;
}

void HTdelete (THT* ht, TKey key) {
    unsigned h = keyHash(key) % ht->n_bucket;
    TInfo info = {key};
    while (ht->used[h] && !infoEqual(info, ht->bucket[h])) 
        h = (h+1) % ht->n_bucket; 
    if (ht->used[h]) { // se ho trovato l'elemento da cancellare...
        unsigned hole = h;    
        ht->used[hole] = 0; // ...rendo disponibile il bucket
        ht->n_used--;
        h = (h+1) % ht->n_bucket;
        while (ht->used[h]) {  // ...e cerco di riempire il buco con un altro elemento
            unsigned h1 = keyHash(ht->bucket[h].key) % ht->n_bucket;
            if ((h > hole && (h1 <= hole || h1 > h)) || (h < hole && h1 > h && h1 <= hole)) {
                // se l'elemento può essere usato per riempire il buco...
                ht->bucket[hole] = ht->bucket[h]; // ...lo sposto nel buco
                ht->used[hole]=1;
                hole = h; // ...e aggiorno l'indice del buco
                ht->used[hole] = 0;  
            }
            h = (h+1) % ht->n_bucket;
        }
    }
}

void HTprint(THT* ht) {
    for (int i = 0; i < ht->n_bucket; i++)
        if (ht->used[i])
            infoPrint (ht->bucket[i]);
}

void HTprintStructure(THT* ht) {
    for (int i = 0; i < ht->n_bucket; i++) {
        printf("Bucket%3d ", i);
        if (ht->used[i]) 
            infoPrint (ht->bucket[i]);
        else 
            printf("(unused)");
        printf("\n");
    }
}
