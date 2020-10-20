#include <stdio.h>
#include "../strutture/TList.h"

/* ESERCIZIO 1
 * Scrivere una funzione RICORSIVA che conti il numero degli elementi di una 
 * lista.
 */

 int listCount (TList list) {
     if (list == NULL)
         return 0;
     return 1 + listCount(list->link);
 }

/* ESERCIZIO 2
 * Scrivere una funzione RICORSIVA che restituisca la somma degli elementi 
 * di una lista di interi.
 */

 int listSum (TList list) {
     if (list == NULL)
         return 0;
     return list->info + listSum(list->link);
 }
 
/* ESERCIZIO 3
 * Scrivere una funzione ITERATIVA che cancelli l’elemento al posto k di una 
 * lista. Per convenzione il primo elemento della lista è associato al valore 
 * 0 dell’indice.
 */

TList listDeleteAt(TList list, int k) {
    
    // ricerca dell'elemento da cancellare
    TNode *prec = NULL, *node = list;
    for (int i = 0; i < k && node != NULL; ++i) {
        prec = node;
        node = node->link;
    }
    
    // cancellazione se l'indice è all'interno della lista
    if (node != NULL) {
        if (prec == NULL) 
            list = node->link; // cancellazione in testa
        else
            prec->link = node->link; // cancellazione in mezzo o in coda
        nodeDestroy(node);
    }
    return list;
}

/* ESERCIZIO 4
 * Scrivere una funzione RICORSIVA che cancelli l’elemento al posto k di una 
 * lista. Per convenzione il primo elemento della lista è associato al valore 
 * 0 dell’indice.
 */

TList listDeleteAtR(TList l, int k) {
    if (l == NULL) 
        return NULL;
    if (k==0) {
        TList m = l->link;
        nodeDestroy(l);
        return m;
    }
    TList m = listDeleteAtR(l->link, k-1);
    l->link = m;
    return l;
}

/* ESERCIZIO 5
 * Scrivere una funzione ITERATIVA che data una lista ordinata L ed un elemento 
 * k, restituisca una nuova lista M che contiene una copia di tutti gli 
 * elementi di L con valori INFERIORI a k (senza modificare L). 
 */

TList copyLessThan(TList l, TInfo k) {
    
    TList m = listCreate();
    TNode *node = l;
    
    while (node != NULL && infoLess(node->info,  k)) {
        m = listInsert(m, node->info);
        node = node->link;
    }
    return m;
}

/* ESERCIZIO 6
 * Scrivere una funzione ricorsiva che riceve in ingresso due liste ordinate L
 * e M e produca in uscita una lista N ottenuta fondendo gli elementi di L
 * con quelli di M. NOTA: non è richiesto che si mantengano le liste originarie, 
 * per cui all’uscita della funzione, L e M risultano essere vuote.
 */

TList listMerge(TList l, TList m) {
    if (l == NULL)
        return m;
    if (m == NULL)
        return l;
    if(infoGreater(l->info, m->info)) {
        TList n = listMerge(l, m->link);
        m->link = n;
        return m;
    }
    TList n = listMerge(l->link, m);
    l->link = n;
    return l;
}

/* 
 * Codice di test
 */

int main() {
    
    TList l = listCreate();
    l = listInsert(l,3);
    l = listInsert(l,2);
    l = listInsert(l,3);
    l = listInsert(l,9);
    l = listInsert(l,7);
    l = listInsert(l,5);
    l = listInsert(l,1);
    
    printf ("Lista L: "); listPrint(l); printf ("\n");
    
    printf("Numero di elementi: %d\n", listCount(l));
    printf("Somma degli elementi: %d\n", listSum(l));

    printf("\nCancello l'elemento in posizione 3\n");
    l = listDeleteAt(l,3); 
    printf ("Lista L: "); listPrint(l); printf ("\n");
    
    printf("\nCancello l'elemento in posizione 0\n");
    l = listDeleteAtR(l,0); 
    printf ("Lista L: "); listPrint(l); printf ("\n");

    printf("\nCopio gli elementi inferiori a 5\n");
    TList m = copyLessThan(l,5); 
    printf ("Lista M: "); listPrint(m); printf ("\n");

    printf("\nFondo L e M in N\n");
    TList n = listMerge (l,m);
    printf ("Lista N: "); listPrint(n); printf ("\n");
}

