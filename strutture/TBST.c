#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "TInfo.h"
#include "TBST.h"

/* operazioni sui nodi */

TBSTnode *BSTnodeCreate (TInfo info) {
    TBSTnode *node = malloc (sizeof(TBSTnode));
    assert (node != NULL);
    node->info = info;
    node->left = node->right = NULL;
    return node;
}

void BSTnodeDestroy (TBSTnode* node) {
    free (node);
}

/* operazioni sugli alberi - versione ricorsiva */

TBST BSTcreate () {
    return NULL;
}

TBST BSTdestroy (TBST tree) {
    if (tree == NULL)
        return NULL;
    BSTdestroy(tree->left);
    BSTdestroy(tree->right);
    BSTnodeDestroy (tree);
    return NULL;
}

TBST BSTsearch (TBST tree, TInfo info) {
    if (tree == NULL || infoEqual(info, tree->info))
        return tree;
    if (infoGreater(info, tree->info)) 
        return BSTsearch(tree->right, info);
    else 
        return BSTsearch(tree->left, info);
    return tree;
}

TBST BSTmin (TBST tree) {
    if (tree == NULL || tree->left == NULL)
        return tree;
    return BSTmin (tree->left);
}

TBST BSTmax (TBST tree) {
    if (tree == NULL || tree->right == NULL)
        return tree;
    return BSTmax (tree->right);
}

TBST BSTinsert (TBST tree, TInfo info) {
    if (tree == NULL)
        return BSTnodeCreate(info);
    if (infoGreater(info, tree->info)) 
        tree->right = BSTinsert(tree->right, info);
    else 
        tree->left = BSTinsert(tree->left, info);
    return tree;
}

TBST BSTdelete (TBST tree, TInfo info) {
    if (tree == NULL)
        return NULL;
    if (infoGreater(info, tree->info)) 
        tree->right = BSTdelete(tree->right, info);
    else if (infoLess(info, tree->info))
        tree->left = BSTdelete(tree->left, info);
    else { // trovato il nodo da rimuovere
        if (tree->left == NULL) {
            TBST right = tree->right;
            BSTnodeDestroy(tree);
            tree = right;
        } else if (tree->right == NULL) {
            TBST left = tree->left;
            BSTnodeDestroy(tree);
            tree = left;
        } else {
            TBST min = BSTmin(tree->right);
            tree->info = min->info;
            tree->right = BSTdelete(tree->right, min->info);
        }
    }
    return tree;
}

int BSTheight(TBST tree) {
    if (tree == NULL)
        return -1;
    int l = BSTheight(tree->left);
    int r = BSTheight(tree->right);
    if (l > r) 
        return l + 1;
    return r + 1;
}

void BSTprint (TBST tree) {
    if (tree != NULL) {
        BSTprint(tree->left);
        infoPrint(tree->info);
        BSTprint(tree->right);
    }
}

/* versione iretativa di alcuni algoritmi */

TBST BSTsearchI (TBST tree, TInfo info) {
    
    while (tree != NULL && !infoEqual(tree->info, info)) {
        if (infoGreater (info,  tree->info))
            tree = tree->right;
        else
            tree = tree->left;
    }
    return tree;
}

TBST BSTinsertI (TBST tree, TInfo info) {
    
    TBSTnode *node = tree;
    TBSTnode *prec = NULL;     
    TBSTnode *new = BSTnodeCreate(info);
    int right;

    /* cerca il punto d'inserimento */
    while (node != NULL) {
        prec = node;
        right = infoGreater (info,  node->info);
        if (right)
            node = node->right;
        else
            node = node->left;
    }     

    /* inserisce il nuovo nodo */
    if(prec == NULL)
        return new;
    if (right) 
        prec->right = new;
    else
        prec->left = new;
    return tree;
}
 
TBST BSTdeleteI (TBST tree, TInfo info) {
    
    TBSTnode *node = tree;
    TBSTnode *prec = NULL;     
    int right;

    /* cerca il nodo da cancellare */  
    while (node != NULL && !infoEqual(node->info, info)) {
        prec = node;
        right = infoGreater (info,  node->info);
        if (right)
            node = node->right;
        else
            node = node->left;
    }     

    /* nodo non trovato */  
    if (node == NULL)
        return tree;

    /* nodo foglia o con un solo figlio */  
    if (node->left == NULL || node->right == NULL) {
        TBSTnode *succ; // nodo da agganciare     
        if (node->right == NULL)
            succ = node->left;
        else
            succ = node->right;
        BSTnodeDestroy(node);
        if (prec == NULL) // è stata cancellata la radice
            return succ;
        else if (right)
            prec->right = succ;
        else
            prec->left = succ;
        return tree;
    }

    /* nodo con entrambi i figli */  
    TBSTnode* min = BSTmin(node->right);
    node->info = min->info; // sostituisce info con il minimo a destra
    prec = node;
    node = node->right;
    right = 1;
    while (node->left != NULL) { // si posiziona sul nodo con il minimo
        prec = node;
        node = node->left;
        right = 0;
    }
    if (right) // lo esclude
        prec->right = node->right;
    else
        prec->left = node->right;
    BSTnodeDestroy(node); // lo rimuove
    return tree;
}

/* funzioni utili a visualizzare la struttura di un albero binario di interi 
 * (valgono solo per TInfo = int)
 */

int BSTdepth(TBST tree){
    if(tree == NULL)
        return -1;
    int hl = BSTdepth(tree->left);
    int hr = BSTdepth(tree->right);
    return (hl > hr)?(hl + 1):(hr + 1);
}

void BSTprintStructure1(TBST tree, int o, TInfo* n, int* m) {
    if (tree != NULL) {
        n[o] = tree->info;
        m[o] = 1;
        BSTprintStructure1(tree->left, (o+1)*2-1, n, m);
        BSTprintStructure1(tree->right, (o+1)*2, n, m);
    }
}

void BSTprintStructure(TBST tree) {
    int d = BSTdepth(tree)+1, s = pow(2,d)-1, m[s], i, j, b;
    TInfo n[s];
    for (i = 0; i < s; ++i) // annulla elementi
        m[i] = 0;
    BSTprintStructure1(tree, 0, n, m);
    for (i = 0; i < d; ++i) { // stampa albero
        for (j = pow(2,i)-1; j < pow(2,i+1)-1; ++j) {
            b = (pow(2,(d-i-1))-1)*4;
            if (m[j])
                printf("%*d%*s", b/2+4, n[j], b/2, "");
            else
                printf("%*s", b+4,  "");
        }
        printf("\n");
    }
}