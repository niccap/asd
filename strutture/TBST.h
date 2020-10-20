#ifndef TBST_H
#define TBST_H

#include "TInfo.h"

struct SBSTnode {
    TInfo info;
    struct SBSTnode *left;
    struct SBSTnode *right;
};

typedef struct SBSTnode TBSTnode;
typedef TBSTnode *TBST;

TBSTnode *BSTnodeCreate(TInfo);
void BSTnodeDestroy(TBSTnode*);
TBST BSTcreate ();
TBST BSTdestroy (TBST);
TBST BSTsearch (TBST, TInfo);
TBST BSTmin (TBST);
TBST BSTmax (TBST);
TBST BSTinsert (TBST, TInfo);
TBST BSTdelete (TBST, TInfo);
TBST BSTsearchI (TBST, TInfo);
TBST BSTinsertI (TBST, TInfo);
TBST BSTdeleteI (TBST, TInfo);
int BSTheight(TBST);
void BSTprint(TBST);
void BSTprintStructure(TBST);

#endif 

