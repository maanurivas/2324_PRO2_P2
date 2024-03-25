/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Ana Gomez Mesias LOGIN 1: ana.gmesias@udc.es
 * AUTHOR 2: Manuel Rivas Capeans LOGIN 2: m.rivas.capeans@udc.es
 * GROUP: 3.3
 * DATE: 18 / 03 / 2024
 */

#include "user_list.h"
#include "song_list.h"

void createEmptyListU (tListU *U){
    *U = NULLU;
}
bool createNode(tPosU *p){
    *p = malloc(sizeof(struct Node));
    return *p != NULLU;
}

bool isEmptyListU(tListU U) {
    return U == NULLU;
}

tPosU firstU(tListU U){
    return U;
}

tPosU lastU(tListU U){
    tPosU p;
    for (p = U; p->next != NULLU ; p = p->next);//Se recorre la lista hasta llegar al final
    return p;
}

tPosU nextU(tPosU p, tListU U){
    return p->next;
}

tPosU previousU(tPosU p, tListU U){
    tPosU q;
    if(p == U){//Si p es la primera posición se devolverá nulo
        return NULLU;
    }
    else{
        for (q = U; q->next != p; q = q->next);//Se recorre la lista hasta llegar a la posición anterior a la indicada
        return q;
    }
}

bool insertItemU(tItemU ITEM, tListU * U) {
    tPosU p, q, prev;

    if (!createNode(&q)) {
        return false; // Error al crear el nodo
    }
    q->data = ITEM;
    q->next = NULLU;
    if (isEmptyListU(*U)) {// Si la lista está vacía, simplemente inserta el nodo al principio
        *U = q;
        return true;
    }
    prev = NULLU;
    p = *U;
    while (p != NULLU && strcmp(p->data.userName, ITEM.userName) < 0) {// Encuentra la posición adecuada para insertar el nodo
        prev = p;
        p = p->next;
    }
    if (prev == NULLU) {// Si la posición es al inicio de la lista, ajusta el puntero de la lista
        q->next = *U;
        *U = q;
    } else {
        prev->next = q;// Inserta el nodo entre prev y p
        q->next = p;
    }
    return true; // Inserción exitosa
}

tPosU findPositionU(tListU U, tItemU ITEM) {
        tPosU p;
        p = U;
        while ((p->next != NULLU) &&(strcmp(ITEM.userName, p->data.userName) < 0)) {
            p = p->next;
        }
        return p;
}


void deleteAtPositionU(tPosU p, tListU *U){
    tPosU q;
    if (p == *U) {//La posición a eliminar es la primera
        *U = p->next;
        free(p);

    }
    else if (p->next == NULLU) {//La posición a eliminar es la última
        previousU(p, *U)->next = NULLU;
        free(p);
    }
    else {//Es una posición intermedia
        q = p->next;
        p->data = q->data;
        p->next = q->next;
        free(q);
    }
}

tItemU getItemU(tPosU p, tListU U){
    return p->data;
}


void updateItemU(tItemU ITEM, tPosU p, tListU * U){
    p->data = ITEM;
}


tPosU findItemU(tUserName userName, tListU U) {
    tPosU p;
    if (isEmptyListU(U)) {
        p = NULLU;
    }
    else{//Se recorre la lista hasta encontrar el elemento o hasta llegar llegar al final
        for (p = U; p != NULLU && strcmp(userName, p->data.userName) != 0; p = p->next);
        if(p != NULLU && (strcmp(userName, p->data.userName) == 0)) return p;
    }
    return p;
}



