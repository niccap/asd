#include <stdio.h>
#include "TBST.h"

/* ESERCIZIO 1
 * Scrivere una funzione RICORSIVA che restituisce l'altezza di un albero
 * binario (la profondità massima a cui si trovano i nodi foglia). La 
 * funzione restituisce -1 in caso di albero nullo.
 */

int BSTheight2(TBST tree) {
    if (tree == NULL)
        return -1;
    int l = BSTheight(tree->left);
    int r = BSTheight(tree->right);
    if (l > r) 
        return l + 1;
    return r + 1;
}

/* ESERCIZIO 2
 * Scrivere una funzione RICORSIVA che restituisce il numero di nodi 
 * di un albero
 */

int BSTcountNodes(TBST tree) {
    if (tree == NULL)
        return 0;
    int l = BSTcountNodes(tree->left);
    int r = BSTcountNodes(tree->right);
    return r + l + 1;
}

/* ESERCIZIO 3
 * Scrivere una funzione RICORSIVA che restituisce il numero di foglie 
 * di un albero
 */

int BSTcountLeaves(TBST tree) {
    if (tree == NULL)
        return 0;
    if (tree->left == NULL && tree->right == NULL)
        return 1;
    int l = BSTcountLeaves(tree->left);
    int r = BSTcountLeaves(tree->right);
    return r + l;
}

/* ESERCIZIO 4
 * Scrivere una funzione RICORSIVA che restituisce la somma dei valori 
 * contenuti in tutti i nodi dell'albero
 */

int BSTsum(TBST tree) {
    if (tree == NULL)
        return 0;
    int l = BSTsum(tree->left);
    int r = BSTsum(tree->right);
    return r + l + tree->info;
}

/* ESERCIZIO 5
 * Scrivere una funzione RICORSIVA che restituisce la somma dei nodi di un 
 * albero binario di interi che si trovano a profondità k.
 */

int BSTsumDepth(TBST tree, int k) {
    if (tree == NULL)
        return 0;
    if (k == 0)
        return tree->info;
    int l = BSTsumDepth(tree->left, k-1);
    int r = BSTsumDepth(tree->right, k-1);
    return l + r;
}

/* ESERCIZIO 6
 * Scrivere una funzione RICORSIVA che visualizza in ordine tutti gli elementi
 * di un BST di interi compresi tra min e max (inclusi gli estremi)
 */

void BSTprintInterval(TBST tree, int min, int max) {
    if (tree == NULL)
        return;
    BSTprintInterval(tree->left, min, max);
    if (!infoGreater(min, tree->info) && !infoLess(max, tree->info)) // min <= tree->info && max >= tree->info
        infoPrint(tree->info);
    BSTprintInterval(tree->right, min, max);
}

/* ESERCIZIO 6 - soluzione più efficiente */

void BSTprintInterval2 (TBST tree, int min, int max) {
    if (tree == NULL)
        return;
    if (!infoGreater(min, tree->info)) // min <= tree->info
        BSTprintInterval2(tree->left, min, max);
    if (!infoGreater(min, tree->info) && !infoLess(max, tree->info)) // min <= tree->info && max >= tree->info
        printf("%d ", tree->info);
    if (!infoLess(max, tree->info)) // max >= tree->info
        BSTprintInterval2(tree->right, min, max);
}

/* ESERCIZIO 7
 * Scrivere una funzione RICORSIVA che restituisce il riferimento al padre di
 * un nodo di un albero binario di cui è noto il riferimento (NULL nel caso 
 * il nodo sia la radice o non sia presente nell'albero).
 */

TBST BSTfather(TBST tree, TBST node) {
    if (tree == NULL || node == NULL || tree == node)
        return NULL;
    if (tree->left == node || tree->right == node)
        return tree;
    TBST father = BSTfather(tree->left, node);
    if (father == NULL)
        return BSTfather(tree->right, node);
    return father;
}

/* ESERCIZIO 7 - soluzione più efficiente */

TBST BSTfather2(TBST tree, TBST node) {
    if (tree == NULL || node == NULL || tree == node)
        return NULL;
    if (tree->left == node || tree->right == node)
        return tree;
    TBST father = NULL;
    if (!infoGreater(node->info, tree->info)) // node->info <= tree->info
        father = BSTfather2(tree->left, node);
    if (father == NULL && !infoLess(node->info, tree->info)) // fatherr == NULL && node->info >= tree->info
        father = BSTfather2(tree->right, node);
    return father;
}

/* ESERCIZIO 8
 * Scrivere una funzione RICORSIVA che restituisce il più piccolo sotto-albero 
 * di un BST contenente due elementi info1 e info2
 */

TBST BSTsubTree(TBST tree, TInfo info1, TInfo info2) {
    if (tree != NULL) {
        if (infoLess(info1, tree->info) && infoLess(info2, tree->info))
            return BSTsubTree(tree->left, info1, info2); 
        if (infoGreater(info1, tree->info) && infoGreater(info2, tree->info))
            return BSTsubTree(tree->right, info1, info2); 
        if (BSTsearch(tree, info1) != NULL && BSTsearch(tree, info2) != NULL)
            return tree;
    }
    return NULL;
}

/* 
 * Codice di test
 */

int main(int argc, char** argv) {
    
    TBST tree, f;
    tree = BSTinsert(tree, 20);
    tree = BSTinsert(tree, 10);
    tree = BSTinsert(tree, 30);
    tree = BSTinsert(tree, 15);
    tree = BSTinsert(tree, 8);
    tree = BSTinsert(tree, 35);
    tree = BSTinsert(tree, 25);
    tree = BSTinsert(tree, 22);
    printf ("Albero:\n");
    BSTprintStructure(tree);
    
    printf ("\nAltezza: %d\n", BSTheight(tree));
    printf ("Numero di nodi: %d\n", BSTcountNodes(tree));
    printf ("Numero di foglie: %d\n", BSTcountLeaves(tree));
    printf ("Somma dei nodi: %d\n", BSTsum(tree));
    printf ("Somma profondità 0: %d\n", BSTsumDepth(tree,0));
    printf ("Somma profondità 1: %d\n", BSTsumDepth(tree,1));
    printf ("Somma profondità 2: %d\n", BSTsumDepth(tree,2));
    printf ("\nElementi tra 10 e 30: "); BSTprintInterval(tree,10,30);printf("\n");

    f = BSTfather2(tree,BSTsearch(tree,15));
    printf ("Padre di 15: %d\n", f == NULL ? -1 : f->info);    
    f = BSTfather2(tree,BSTsearch(tree,10));
    printf ("Padre di 10: %d\n", f == NULL ? -1 : f->info);    
    f = BSTfather2(tree,BSTsearch(tree,20));
    printf ("Padre di 20: %d\n", f == NULL ? -1 : f->info);    
    
    f = BSTsubTree(tree,8,15);
    printf ("Il sottoalbero che include 8 e 15 ha radice in: %d\n", f == NULL ? -1 : f->info);    
    f = BSTsubTree(tree,15,30);
    printf ("Il sottoalbero che include 15 e 30 ha radice in: %d\n", f == NULL ? -1 : f->info);    
    f = BSTsubTree(tree,17,35);
    printf ("Il sottoalbero che include 17 e 35 ha radice in: %d\n\n", f == NULL ? -1 : f->info);    

    return 0;
}
