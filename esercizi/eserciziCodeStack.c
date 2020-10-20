// gcc eserciziCodeStack.c ../strutture/TQueue.c ../strutture/TStack.c ../strutture/TArray.c ../strutture/TInfo.c

#include <stdio.h>
#include "../strutture/TQueue.h"
#include "../strutture/TStack.h"

/* 
 * ESERCIZIO 1
 * Realizzare la funzione queuePrint che stampa i valori di una coda.
 */

/* v1 - stampiamo ma distruggiamo la coda. */
void queuePrint1(TQueue *q) {
    while (!queueIsEmpty(q))
        printf("%d ", queueRemove(q)); 
    printf("\n"); 
}

/* v2 - utilizziamo il valore q->n che non sempre è disponibile. */
void queuePrint2(TQueue *q) {
    for (int i = 0; i < q->n; i++) {
        printf("%d ", queueFront(q)); 
        queueAdd (q, queueRemove(q));
    }
    printf("\n"); 
}

/* v3 - versione formalmente corretta ma poco efficiente. */
void queuePrint3(TQueue *q) {
    TQueue r = queueCreate();
    while (!queueIsEmpty(q)) {
        printf("%d ", queueFront(q)); 
        queueAdd (&r, queueRemove(q));
    }
    printf("\n"); 
    while (!queueIsEmpty(&r)) 
        queueAdd (q, queueRemove(&r));
    queueDestroy(&r);
}

/* v4 - versione più efficiente. */
void queuePrint4(TQueue *q) {
    TQueue r = queueCreate();
    while (!queueIsEmpty(q)) {
        printf("%d ", queueFront(q)); 
        queueAdd (&r, queueRemove(q));
    }
    printf("\n"); 
    queueDestroy(q);
    *q = r;
}

/* 
 * ESERCIZIO 2
 * Realizzare la funzione queueReverse che inverte i valori di una coda. 
 */

/* v1 - utilizza uno stack per invertire i valori */
void queueReverse1(TQueue *q) {
    TStack s = stackCreate();
    while (!queueIsEmpty(q))
        stackPush(&s, queueRemove(q));
    while (!stackIsEmpty(&s))
        queueAdd(q, stackPop(&s));
    stackDestroy(&s);
}

/* 
 * v2 - versione ricorsiva
 *
 * DIVIDE: la coda q=(q1,...,qn) viene divisa considerando separatamente il
 * front q1 e la coda q'=(q2,...,qn) 
 * 
 * CASO BASE: se q è vuota allora il risultato è q
 * 
 * IMPERA: si suppone per ipotesi induttiva che si sappia risolvere il problema
 * per la coda q' e che il risultato sia r'=(qn,...,q2)
 * 
 * COMBINA: il risultato si ottiene accodando q1 a r'
 */

void queueReverse2(TQueue *q) {
    if (queueIsEmpty(q))
        return;
    TInfo x = queueRemove(q);
    queueReverse2(q);
    queueAdd(q, x);
}

/* 
 * ESERCIZIO 3
 * Realizzare una funzione che restituisce la somma degli elementi di una coda
 */

/* v1 - versione iteratva basata su q->n */
int queueSum1 (TQueue* q) {
    TInfo sum = 0;
    for (int i = 0; i < q->n; ++i) {
        sum += queueFront(q);
        queueAdd(q, queueRemove(q));
    }
    return sum;
}

/* v2 - versione iteratva che non usa q->n */
int queueSum2 (TQueue* q) {
    TQueue r = queueCreate();
    TInfo sum = 0;
    while (!queueIsEmpty(q)) {
        sum += queueFront(q);
        queueAdd(&r, queueRemove(q));
    }
    queueDestroy(q);
    *q = r;
    return sum;
}

/* 
 * versioni ricorsive
 *
 * DIVIDE: la coda q=(q1,...,qn) viene divisa considerando separatamente il
 * front q1 e la coda q'=(q2,...,qn) 
 * 
 * CASO BASE: se q è vuota allora il risultato è 0
 * 
 * IMPERA: si suppone per ipotesi induttiva che si sappia risolvere il problema
 * per la coda q' e che il risultato sia s
 * 
 * COMBINA: il risultato si ottiene sommando q1 a s
 */


/* v3 - distrugge la coda */
int queueSum3 (TQueue* q) {
    if (queueIsEmpty(q))
        return 0;
    TInfo i = queueRemove(q);
    return i + queueSum3(q);
}

/* v4 - inverte la coda */
int queueSum4 (TQueue* q) {
    if (queueIsEmpty(q))
        return 0;
    TInfo i = queueRemove(q);
    TInfo sum = queueSum4(q);
    queueAdd(q, i);
    return sum + i;
}

/* v5 - ripristina la coda invertita */
int queueSum5 (TQueue* q) {
    TInfo sum = queueSum4(q);
    queueReverse1(q);
    return sum;
}

/*
 * Codice di test
 */

int main() {
    TQueue q = queueCreate();
    int i;    
    
    printf("Inserisci una sequenza di interi seguiti da una lettera: ");
    while (scanf ("%d", &i) != 0)
        queueAdd (&q, i);

    queuePrint2(&q);
    printf("Inverto...\n");
    queueReverse1(&q);
    queuePrint3(&q);
    printf("Inverto di nuovo...\n");
    queueReverse2(&q);
    queuePrint4(&q);
    printf("La somma dei valori è: %d\n", queueSum1(&q));
    printf("La somma dei valori è: %d\n", queueSum2(&q));
    printf("La somma dei valori è: %d\n", queueSum5(&q));
    
    queueDestroy(&q);
}

