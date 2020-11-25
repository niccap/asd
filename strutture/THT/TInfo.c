/*
 * TInfo: tipo elementare
 */

#include <stdio.h>
#include <string.h>
#include "TInfo.h"

int infoEqual (TInfo info1, TInfo info2) {
    return info1.key == info2.key;
}

int infoGreater (TInfo info1, TInfo info2) {
    return  info1.key > info2.key;
}

int infoLess (TInfo info1, TInfo info2) {
    return  info1.key < info2.key;
}

void infoPrint (TInfo info) {
    printf ("(%d: %f) ", info.key, info.value);

    /* con TValue alternativo
    printf ("(%d: %s, %.2f) ", info.key, info.value.name, info.value.price);
    */
}

unsigned int keyHash (TKey key) {
    return key;
}