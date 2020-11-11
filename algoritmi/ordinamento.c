#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../strutture/TInfo.h"

/*
 * Funzioni di utilità
 */

void swap(TInfo* x, TInfo* y) {
    TInfo z = *x;
    *x = *y;
    *y = z;
}

void printArray(TInfo a[], int n) {
    for (int i = 0; i < n; i++)
        printf ("%d ", a[i]);
    printf ("\n");
}

void copyArray(TInfo a[], TInfo b[], int n) {
    for (int i = 0; i < n; i++)
        b[i]=a[i];
}

/* 
 * Ricerca l'indice del minimo di un array
 */

int searchMin(TInfo a[], int n) {
    TInfo min = 0;              
    for (int i = 1; i < n; i++) 
        if (infoLess(a[i], a[min]))  
            min = i;             
    return min;      
}

/* 
 * Selection Sort
 */

void selectionSort(TInfo a[], int n) {
    for (int i = 0; i < n-1; i++) {         
        int min = i + searchMin(a+i, n-i);  
        if (min != i)                     
            swap (&a[i], &a[min]);         
    }
}

/* 
 * Inserimento in order di x in a (a può contenere n+1 elementi)
 */

void insertInOrder(TInfo a[], int n, TInfo x) {
    int pos;                                               
    for (pos = n; pos > 0 && infoGreater (a[pos-1], x); pos--) 
        a[pos] = a[pos-1];                            
    a[pos]=x;                            
}

/* 
 * Insertion Sort
 */

void insertionSort(TInfo a[], int n) { 
    for (int i = 1; i < n; i++)   
        insertInOrder(a, i, a[i]);
}

/* 
 * Bubble Sort
 */

void bubbleSort (TInfo a[], int n)
{
    int mod=1;
    for (int k=0; k<n-1 && mod; k++) {
        mod = 0;
        for (int i=0; i<n-k-1; i++) 
            if (infoGreater(a[i],a[i+1])) {
                swap(&a[i], &a[i+1]);
                mod=1;
            }
    }
}

/* 
 * Fusione di due array ordinati a1 e a2 in un nuovo array ordinato b
 */

void merge(TInfo a1[], int n1, TInfo a2[], int n2, TInfo b[]) {
    int i1 = 0, i2 = 0, j = 0;
    
    while (i1 < n1 && i2 < n2) {
        if (infoLess(a1[i1], a2[i2]))
            b[j++] = a1[i1++];
        else
            b[j++] = a2[i2++];
    }
    while (i1 < n1)
        b[j++] = a1[i1++];
    while (i2 < n2)
        b[j++] = a2[i2++];
}

/* 
 * Merge Sort
 */

/* versione con allocazione dinamica dell'array temporaneo */
void mergeSort(TInfo a[], int n) {
    if (n <= 1)
        return;
    
    int m = n/2;
    mergeSort(a, m);
    mergeSort(a+m, n-m);

    TInfo temp[n];
    merge(a, m, a+m, n-m, temp);
    for (int i = 0; i<n; ++i)
        a[i] = temp[i];
}

/* 
 * Partizionamento di un array rispetto ad un elemento pivot, restituisce 
 * l'indice aggiornato del pivot
 */

int partition(TInfo a[], int n) {
    int k = 1; // primo elemento della seconda partizione
    for (int i = 1; i<n; i++)
        if (infoLess(a[i], a[0]))
            swap (&a[i], &a[k++]);
    swap(&a[0], &a[k-1]); // posiziona il pivot
    return k-1;
}

/* 
 * Quick Sort
 */

void quickSort(TInfo a[], int n) {
    if (n <= 1)
        return;
    int k = partition(a, n);
    quickSort(a, k);
    quickSort(a+k+1, n-k-1);
}

/*
 * codice di test (per TInfo alias di int)
 */

#define size 1000  // dimensione array di esempio
#define max  1000  // massimo valore nell'array

int main(int argc, char** argv) {

    srand(time(NULL)); // inizializza il generatore di numeri casuali
    int a[size], b[size];
    for (int i = 0; i<size; ++i) // genera un array di interi tra 0 e max-1
        a[i]=rand()%max;
    
    printf ("Array di partenza:\n");
    printArray(a, size);
    
    copyArray(a, b, size);    
    clock_t cc = clock();
    selectionSort(b, size);
    printf ("\nSelectionSort (%lu cc):\n", clock()-cc);
    printArray(b, size);

    copyArray(a, b, size);    
    cc = clock();
    insertionSort(b, size);
    printf ("\nInsertionSort (%lu cc):\n", clock()-cc);
    printArray(b, size);

    copyArray(a, b, size);    
    cc = clock();
    bubbleSort(b, size);
    printf ("\nBubbleSort (%lu cc):\n", clock()-cc);
    printArray(b, size);

    copyArray(a, b, size);    
    cc = clock();
    mergeSort(b, size);
    printf ("\nMergeSort (%lu cc):\n", clock()-cc);
    printArray(b, size);

    copyArray(a, b, size);    
    cc = clock();
    quickSort(b, size);
    printf ("\nQuickSort (%lu cc):\n", clock()-cc);
    printArray(b, size);
}

