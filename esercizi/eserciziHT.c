#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "../strutture/THT/THT.h"

/*
 * ESERCIZIO 1
 * Scrivere una funzione che, se esiste un valore associato con 
 * una chiave key ne incrementa di 1 il valore, altrimenti inserisce 
 * nella tabella hash il dato (key, 1)
 */

void HTincrease(THT *ht, TKey key) {   
    TValue *v = HTsearch(ht, key);
    if (v == NULL)
        HTinsert (ht, key, 1);
    else
        (*v)++;
}

/*
 * ESERCIZIO 2
 * Scrivere una funzione che prende in input un puntatore ad una HT oltre che 
 * i valori key e newKey. Se esiste un elemento nella HT con chiave key 
 * allora sostituisce la sua chiave con newKey
 */

void changeKey(THT *ht, TKey key, TKey newKey) {
    TValue *v = HTsearch(ht, key);
    if (v != NULL) {
        HTinsert(ht, newKey, *v);
        if (key != newKey)
            HTdelete(ht, key);
    }
}

/*
 * ESERCIZIO 3
 * Scrivere una funzione che restituisce una lista (ordinata per chiave) che 
 * include tutte le coppie chiave:valore di una hash table per cui la chiave è 
 * compresa tra due valori min e max
 */

/* VERSIONE PER HT A INDIRIZZAMENTO CHIUSO */
TList HTextractList(THT* ht, TKey min, TKey max) {
    TList list = listCreate();
    TInfo imin = {min}, imax = {max};
    for (int i = 0; i < ht->n_bucket; i++)
        for (TNode *node = ht->bucket[i]; node != NULL; node = node->link)
            if (!infoLess(node->info, imin) && !infoGreater(node->info, imax))
                list = listInsert(list,node->info);
    return list;
}

/* VERSIONE PER HT A INDIRIZZAMENTO APERTO
TList HTextractList(THT* ht, TKey min, TKey max) {
    TList list = listCreate();
    TInfo imin = {min}, imax = {max};
    for (int i = 0; i < ht->n_bucket; i++)
        if (ht->used[i] && !infoLess(ht->bucket[i], imin) && !infoGreater(ht->bucket[i], imax))
            list = listInsert(list,ht->bucket[i]);
    return list;
} */

/*
 * ESERCIZIO 4
 * Scrivere una funzione che inserisce in una HT tutte le coppie chiave:valore 
 * di una lista solo se la chiave non è già presente nella HT
 */

void HTmergeList(THT* ht, TList list) {
    if (list == NULL)
        return;
    HTmergeList(ht, list->link);
    if (HTsearch(ht, list->info.key) == NULL)
        HTinsert(ht, list->info.key, list->info.value);
}

/*
 * ESERCIZIO 5
 * Scrivere una funzione che elimina da una HT tutte le chiavi che collidono
 * con una chiave passata come argomento
 */

/* VERSIONE PER HT A INDIRIZZAMENTO CHIUSO */
void HTdeleteColliding(THT* ht, TKey key) {
    unsigned h = keyHash(key) % ht->n_bucket;
    TInfo info = {key};
    TNode *node = listSearch(ht->bucket[h], info);
    if (node != NULL) {
        info = node->info;
        ht->bucket[h] = listDestroy(ht->bucket[h]);
        ht->bucket[h] = listCreate();
        ht->bucket[h] = listInsert(ht->bucket[h], info);
    }
}

/* VERSIONE PER HT A INDIRIZZAMENTO APERTO
void HTdeleteColliding(THT* ht, TKey key) {
    if (HTsearch(ht,key) != NULL) {
        unsigned h = keyHash(key) % ht->n_bucket, h2 = h;
        while (ht->used[h2]) {
            TKey key2 = ht->bucket[h2].key;
            if (key2 != key && keyHash(key2) % ht->n_bucket == h) // chiave che collide
                HTdelete(ht, ht->bucket[h2].key);
            else
                h2 = (h2+1) % ht->n_bucket; 
        }
    }
} */

/*
 * ESERCIZIO 6
 * Realizzare una funzione che incrementa di 1 tutte le chiavi di una hash table. 
 */

/* VERSIONE PER HT A INDIRIZZAMENTO CHIUSO */
void HTkeyIncrement(THT *ht) {
    TList list = listCreate();
    for (int i = 0; i < ht->n_bucket; i++)
        while (ht->bucket[i] != NULL) {
            list = listInsert(list,ht->bucket[i]->info);
            HTdelete (ht, ht->bucket[i]->info.key);
        }
    for (TNode *node = list; node != NULL; node = node->link)
        HTinsert(ht, node->info.key+1, node->info.value);
    listDestroy(list);
}

/* VERSIONE PER HT A INDIRIZZAMENTO APERTO
void HTkeyIncrement(THT *ht) {
    TList list = listCreate();
    for (int i = 0; i < ht->n_bucket; i++)
        if (ht->used[i]) 
            list = listInsert(list,ht->bucket[i]);
    for (TNode *node = list; node != NULL; node = node->link)
        HTdelete (ht, node->info.key);
    for (TNode *node = list; node != NULL; node = node->link)
        HTinsert(ht, node->info.key+1, node->info.value);
    listDestroy(list);
} */

/* Codice di Test */

int main(int argc, char** argv) {
    
    THT *ht = HTcreate(10);
    HTincrease(ht, 1000);
    HTincrease(ht, 1111);
    HTincrease(ht, 1111);
    HTincrease(ht, 1871);
    HTincrease(ht, 1171);
    printf("Hash Table dopo gli increase: ");
    HTprint(ht);
    
    changeKey (ht, 1000, 1001);
    changeKey (ht, 1111, 1871);
    printf("\nHash Table dopo i changeKey: ");
    HTprint(ht);

    TList list = HTextractList(ht, 1000, 1500);
    printf("\nLista degli elementi con chiave tra 1000 e 1500: ");
    listPrint(list);

    listDestroy(list);
    list = listCreate();
    list = listInsert(list, (TInfo) {2020, 5.22});
    list = listInsert(list, (TInfo) {1870, 6.22});
    list = listInsert(list, (TInfo) {1171, 5.99});
    list = listInsert(list, (TInfo) {1386, 8.17});
    list = listInsert(list, (TInfo) {1001, 2.99});
    printf("Lista degli elementi da inserire: ");
    listPrint(list);

    HTmergeList(ht, list);
    printf("Hash Table dopo l'inserimento: ");
    HTprint(ht);
    printf("\nStruttura Hash Table:\n");
    HTprintStructure(ht);

    HTdeleteColliding(ht, 1171);
    printf("Dopo l'eliminazione degli elementi collidenti con 1171: ");
    HTprint(ht);
    printf("\nStruttura Hash Table:\n");
    HTprintStructure(ht);

    HTkeyIncrement(ht);
    printf("Dopo l'incremento delle chiavi:\n");
    HTprintStructure(ht);

    HTdestroy(ht);
    listDestroy(list);
}
