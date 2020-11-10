#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../strutture/TInfo.h"

/* Ricerca lineare
 * restituisce l'indice del primo elemento di a uguale a x, -1 se x non è
 * presente in a.
 */

int linearSearch(TInfo a[], int n, TInfo x) {
    int i = 0;
    while (i < n && !infoEqual(a[i], x))
        i++;
    if (i == n) // non trovato
        return -1;
    else
        return i;
}

/* Ricerca lineare (per array ordinati)
 * restituisce l'indice del primo elemento di a uguale a x, -1 se x non è
 * presente in a.
 */

int linearSearchO(TInfo a[], int n, TInfo x) {
    int i = 0;
    while (i < n && infoLess(a[i], x))
        i++;
    if (i == n || infoGreater(a[i], x)) // non trovato
        return -1;
    else
        return i;
}

/* Ricerca binaria (solo per array ordinati)
 * restituisce l'indice del primo elemento di a uguale a x, -1 se x non è
 * presente in a.
 */

int binarySearch(TInfo a[], int n, TInfo x) {
    int first = 0, last = n-1, i;
    while (first <= last) {
        i = (first+last)/2;
        if (infoEqual(a[i], x)) // trovato
            return i;
        if (infoLess(a[i], x))
            first = i+1;
        else
            last = i-1;
    }
    return -1; // non trovato
}

/* Ricerca binaria (algoritmo ricorsivo)
 * restituisce l'indice del primo elemento di a uguale a x, -1 se x non è
 * presente in a.
 */

int binarySearchR(TInfo a[], int n, TInfo x) {
    if (n <= 0)
        return -1; // non trovato
    int i = (n-1)/2;
    if (infoEqual(a[i], x)) // trovato
        return i;
    if (infoLess(a[i], x)) 
        return binarySearch(a, i, x);
    int j = binarySearch(a+i+1, n-i-1, x);
    if (j == -1)
        return -1;
    return j+i+1;
}

/*
 * codice di test (per TInfo alias di int)
 */

#define size 1000000 // dimensione array di esempio

int main(int argc, char** argv) {
    
    int a[size]; // genera un array ordinato di numeri pari 
    for (int i = 0; i<size; ++i)
        a[i]=i*2;
    
    while (1) {
        int x;
        printf ("\nNumero da cercare, (-1 per uscire): ");
        scanf("%d", &x);
        if (x == -1) break;
        
        clock_t cc = clock(); // cicli di clock dall'inizio del programma
        printf ("LinearSearch:  %d in posizione %d (%lu cc)\n", x, 
                linearSearch(a,size,x), clock()-cc);
        cc = clock();     
        printf ("LinearSerachO: %d in posizione %d (%lu cc)\n", x, 
                linearSearchO(a,size,x), clock()-cc);
        cc = clock();     
        printf ("BinarySerach:  %d in posizione %d (%lu cc)\n", x, 
                binarySearch(a,size,x), clock()-cc);
        cc = clock();     
        printf ("BinarySerachR: %d in posizione %d (%lu cc)\n", x, 
                binarySearchR(a,size,x), clock()-cc);            
    }
}

