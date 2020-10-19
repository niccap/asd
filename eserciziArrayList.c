#include <stdio.h>
#include "TList.h"
#include "TArray.h"

/* ESERCIZIO 1
 * Scrivere una funzione ricorsiva printArray che stampa gli elementi di un 
 * array dinamico 
 * 
 * Soluzione 1 - taglio in coda
 * DIVIDE:    a = (a1, ..., an) viene diviso in a' = (a1, ..., an-1) e an
 * CASO BASE: se n == 0 allora non stampa nulla
 * IMPERA:    si suppone per ipotesi induttiva che si sappia stampare a'
 * COMBINA:   si stampa a' e poi an
 */

void arrayPrint1(TArray *a) {
    if (a->length == 0)
        return;
    a->length--;
    arrayPrint(a);
    a->length++;
    infoPrint(a->items[a->length-1]);
}

/*
 * Soluzione 2 - taglio in testa
 * 
 * DIVIDE:    a = (a1, ..., an) viene diviso in a1 e a' = (a2, ..., an)
 * CASO BASE: se n == 0 allora non stampa nulla
 * IMPERA:    si suppone per ipotesi induttiva che si sappia stampare a'
 * COMBINA:   si stampa an e poi a'
 */

void arrayPrint2(TArray *a) {
    if (a->length == 0)
        return;
    infoPrint(a->items[0]);
    a->items++; a->length--; a->size--;
    arrayPrint(a);
    a->items--; a->length++; a->size++;
}

/* ESERCIZIO 2
 * Scrivere una funzione ricorsiva arrayCumulate che modifica un array 
 * dinamico di interi sommando al valore di ciascun elemento quello di tutti 
 * gli elementi precedenti.
 * 
 * Dato l'array a = (a1, a2, ..., an) in input si vuole ottenere in output
 * l'array b = (a1, a1 + a2, ..., a1 + ... + an)
 * 
 * DIVIDE:    a = (a1, ..., an) viene diviso in a' = (a1, ..., an-1) e an
 * CASO BASE: se n <= 1 allora b = a
 * IMPERA:    si suppone per ipotesi induttiva che si sappia risolvere il problema
 *            per l'array a' e che il risultato sia b' = (b1, ..., bn-1) 
 * COMBINA:   b = (b', an + bn-1)
 */

void arrayCumulate(TArray *a) {
    if (a->length <= 1)
        return;    
    TInfo i = a->items[a->length-1];
    a->length--;
    arrayCumulate(a);
    a->length++;
    a->items[a->length-1] = i + a->items[a->length-2];
}

/* ESERCIZIO 3
 * Scrivere una funzione ricorsiva listCumulate che modifica una lista  
 * di interi sommando al valore di ciascun elemento quello di tutti gli elementi 
 * successivi.
 * 
 * Data la lista a = (a1, a2, ..., an) in input si vuole ottenere in output
 * la lista b = (a1 + ... + an, a2 + ... + an, ..., an)
 * 
 * DIVIDE:    a = (a1, ..., an) viene diviso in a1 e a' = (a2, ..., an)
 * CASO BASE: se n <= 1 allora b = a
 * IMPERA:    si suppone per ipotesi induttiva che si sappia risolvere il problema
 *            per l'array a' e che il risultato sia b' = (b1, ..., bn-1) 
 * COMBINA:   b = (a1 + b1, b')
 */

void listCumulate(TList a) {
    if (a == NULL || a->link == NULL)
        return;
    listCumulate(a->link);
    a->info += a->link->info;
}

/* ESERCIZIO 4
 * Scrivere una funzione ricorsiva listCumulate che modifica una lista  
 * di interi sommando al valore di ciascun elemento quello di tutti gli elementi 
 * precedenti.
 * 
 * Data la lista a = (a1, a2, ..., an) in input si vuole ottenere in output
 * la lista b = (a1, a1 + a2, ..., a1 + ... + an)
 * 
 * DIVIDE:    a = (a1, ..., an) viene diviso in a1 e a' = (a1 + a2, a3, ..., an)
 * CASO BASE: se n <= 1 allora b = a
 * IMPERA:    si suppone per ipotesi induttiva che si sappia risolvere il problema
 *            per l'array a' e che il risultato sia b' = (b1, ..., bn-1) 
 * COMBINA:   b = (a1, b')
 */

void listCumulate2(TList a) {
    if (a == NULL || a->link == NULL)
        return;
    a->link->info += a->info;
    listCumulate2(a->link);
}

/* ESERCIZIO 5
 * Scrivere una funzione ricorsiva separateEven che prende in input una lista e un
 * array dinamico vuoto e che inserisce nell'array tutti i numeri pari presenti nella 
 * lista rimuovendoli da quest'ultima.
 * 
 * Data la lista a = (a1, a2, ..., an) in input si vuole ottenere in output
 * la lista b che contiene i dispari e l'array c che contiene i pari
 * 
 * DIVIDE:    a = (a1, ..., an) viene diviso in a1 e a' = (a2, ..., an)
 * CASO BASE: se n == 0 allora b e c non cambiano
 * IMPERA:    si suppone per ipotesi induttiva che si sappia risolvere il problema
 *            per l'array a' e che i risultati siano b' e c' 
 * COMBINA:   se a1 è pari allora b = (a1, b') e c = c'
 *            se a1 è dispari allora b = b' e c = (c', a1)
 */

TList separateEven(TList l, TArray *a) {
    if (l == NULL)
        return l;
    TList m = separateEven(l->link, a);
    if (l->info % 2 == 0) {
        arrayResize(a, a->length+1);
        a->items[a->length-1] = l->info;
        nodeDestroy(l);
        return m;
    }
    l->link = m;
    return l;
}

/* ESERCIZIO 6
 * Implementare la funzione ricorsiva selectiveFill che memorizza nella posizione i 
 * di in un array dinamico (inizialmente vuoto) il numero di occorrenze del valore i in 
 * una lista ordinata in input e restituisce il valore massimo memorizzato nella lista.
 * 
 * Esempio. lista in input: 0,1,1,2,3,3,3,4,5,5,5,6,8,12,12,14,16,16
 *          array in output: 1,2,1,3,1,3,1,0,1,0,0,0,2,0,1,0,2
 *          valore restituito: 16
 * 
 *  Sia a la lista in input, b l'array in output e max il valore restituito.
 * 
 * DIVIDE:    la lista a = (a1, ..., an) viene divisa in a1 e a' = (a2, ..., an)
 * CASO BASE: se n == 0 allora b è vuoto e max = 0
 * IMPERA:    si suppone per ipotesi induttiva che si sappia risolvere il problema
 *            per a' e che i risultati siano l'array b' e il valore max' 
 * COMBINA:   si assegna b = b' e si incrementa di 1 il valore b[a1], se b
 *            ha meno di a1 elementi allora si ridimensiona e la nuova lunghezza 
 *            è a1; max è la lunghezza di b
 */

int selectiveFill(TList l, TArray *a) {
    if (l == NULL)
        return 0;
    int max = selectiveFill(l->link, a);
    if (l->info > a->length-1) { /* ridimensiona l'array se necessario */
        int len = a->length;
        arrayResize(a, l->info + 1);
        for (int i = len; i < a->length; ++i)
            a->items[i] = 0; /* azzera i nuovi elementi */
    }
    a->items[l->info]++;
    return a->length-1;
}

/* versione iterativa */
int selectiveFill2(TList l, TArray *a) {
	TNode *n = l;
	int max = 0;
	while (n != NULL) { /* cerca il massimo */
		max = n->info;
		n = n->link;
	}
	arrayResize(a, max + 1); /* ridimensiona l'array */
	for (int i = 0; i < a->length; i++) /* azzera i valori */
		a->items[i] = 0;
	n = l;
	while (n != NULL) { /* conta le occorrenze */
		a->items[n->info]++;
		n = n->link;
	}
	return max; 
}

/* ESERCIZIO 7
 * Scrivere una funzione ricorsiva maskList che prende in input una lista di interi 
 * e un array dinamico della stessa dimensione che contiene solo valori 1 o 0.
 * La funzione rimuove dalla lista tutti gli elementi che occupano la stessa posizione
 * di uno 0 nell'array mentre lascia inalterati gli altri.
 * 
 * Esempio. lista in input: 10 15 20 25 27 30 45
 *          array in input: 0  0  1  0  1  1  0
 *          lista in output: 20 27 30
 * 
 * Sia l la lista in input, a l'array in input e m la lista in output.
 * 
 * DIVIDE:    l = (l1, ..., ln) e a = (a1, ..., an) vengono divisi in 
 *            l1, l' =(l2, ..., ln), a1, a' = (a2, ..., an)
 * CASO BASE: se n == 0 allora m è vuota
 * IMPERA:    si suppone per ipotesi induttiva che si sappia risolvere il problema
 *            per l' e a' e che il risultato sia m' 
 * COMBINA:   se a1 = 0 allora m = m' altrimenti m = (l1, m')
 */

TList maskList(TList l, TArray *a) {

    if (l == NULL)
        return l;

    a->items++; a->length--; a->size--;
    TList m = maskList(l->link, a);
    a->items--; a->length++; a->size++;

    if (a->items[0] == 0) {
        nodeDestroy(l);
        return m;
    }
    l->link = m;
    return l;
}

/* 
 * Codice di test
 */

int main() {
    TArray a = arrayCreate(6);
    a.items[0] = 1;
    a.items[1] = 5;
    a.items[2] = 7;
    a.items[3] = 0;
    a.items[4] = 9;
    a.items[5] = 3;

    /* inserisco i valori dell'array in una lista */
    TList l = listCreate();
    for (int i = 0; i < a.length; ++i)
        l = listInsert(l, a.items[i]);

    printf ("Array: "); arrayPrint(&a); printf ("\n");
    arrayCumulate(&a);
    printf ("Array cumulato: "); arrayPrint2(&a); printf ("\n");

    printf ("Lista: "); listPrint(l); printf ("\n");
    listCumulate2(l);
    printf ("Lista cumulata: "); listPrint(l); printf ("\n");
    
    TArray b = arrayCreate(0);
    l = separateEven(l, &b);
    printf ("Lista dei dispari: "); listPrint(l); printf ("\n");
    printf ("Array dei pari: "); arrayPrint(&b); printf ("\n");

    /* modifico la lista */
    l = listDelete(l, 16);
    l = listDelete(l, 25);
    l = listInsert(l, 1);
    l = listInsert(l, 2);
    l = listInsert(l, 2);
    l = listInsert(l, 3);
    l = listInsert(l, 7);
    l = listInsert(l, 6);
    l = listInsert(l, 7);
    printf ("Nuova lista: "); listPrint(l); printf ("\n");

    TArray c = arrayCreate(0);
    int max = selectiveFill(l, &c);
    printf ("Array dei conteggi: "); arrayPrint(&c); printf ("\n");
    printf ("Massimo: %d\n", max);

}

