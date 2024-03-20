/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Ana Gomez Mesias LOGIN 1: ana.gmesias@udc.es
 * AUTHOR 2: Manuel Rivas Capeans LOGIN 2: m.rivas.capeans@udc.es
 * GROUP: 3.3
 * DATE: 18 / 03 / 2024
 */

#include "song_list.h"
#include <string.h>

void createEmptyListS(tListS *S){
    S->lastPos = NULLS;
}

bool isEmptyListS(tListS S) {
    return S.lastPos == NULLS;
}

tPosS firstS(tListS S){
    return 0;
}

tPosS lastS(tListS S){
    return S.lastPos;
}

tPosS nextS(tPosS p, tListS S){
    if(p==S.lastPos)
        return NULLS;
    else
        return ++p;
}

tPosS previousS(tPosS p, tListS S){
    return --p;
}

bool insertItemS(tItemS ITEM, tPosS p, tListS *S){
    tPosS i;
    if(S->lastPos==MAX-1){
        return false;
    }else{
        S->lastPos ++;
        if(p == NULLS){       //Vamos a insertar al final, por lo que vamos a recorrer la lista desde el final.
            S->data[S->lastPos] = ITEM;
        } else{
            for (i=S->lastPos; i >= p+1; i--){
                S->data[i]= S->data[i-1];
            }
            S->data[p]= ITEM;
        }
        return true;
    }
}

void deleteAtPositionS(tPosS p, tListS *S){
    tPosS i;
    S->lastPos--;
    for(i = p; i <= S->lastPos; i++){ //Recorre la lista desde p hatsa la ultima posición.
        S->data[i] = S->data[i+1]; //Cambia el contenido de la posición i por el de la siguiente posición
    }
}

tItemS getItemS(tPosS p, tListS S){
    return S.data[p];
}


void updateItemS(tItemS ITEM, tPosS p, tListS * S){
    (* S).data[p]=ITEM;
}


tPosS findItemS(tUserName name, tListS S) {
    tPosS i;
    if (isEmptyListS(S)) {
        return NULLS;
    }
    else {
        for (i = 0; (i < S.lastPos) && (strcmp(name, S.data[i].songTitle) != 0); i++); //Recorre la lista hasta que llegue al final o encuentre el nombre.
        if (strcmp(name, S.data[i].songTitle) == 0) { // Comprobamos si encontro el nombre con string compare
            return i;
        } else {
            return NULLS;
        }
    }
}