#include <stdio.h>
#include <stdlib.h>

/* ================ Fine strutture dati ================ */
//
/* ------------ Lista collegata ------------ */
typedef struct linkedListNode_t
{
        // Value contained in the node.
        int value;
        // Pointer to next node.
        struct linkedListNode_t *next;
        // Pointer to previous node.
        struct linkedListNode_t *prev;
} linkedListNode_t;

typedef struct linkedList_t
{
        // Size in number of nodes of the list.
        unsigned int size;
        // Pointer to the head node of the list.
        struct linkedListNode_t *head;
} linkedList_t;
/* ------------ Fine Lista collegata ------------ */
//
/* ------------ Tabella HASH ------------ */

typedef struct hashtableEntry_t
{
        // Pointer to the list.
        struct linkedList_t *list;
} hashtableEntry_t;

typedef struct hashtable_t
{
        // Size in number of entries of the hashtable.
        unsigned int size;
        // Array of pointers to entries.
        struct hashtableEntry_t **entry;
} hashtable_t;
/* ------------ Fine Tabella HASH ------------ */
//
/* ================ Fine strutture dati ================ */
//
/* ================ Metodi ================ */

void listInsert(linkedList_t L, linkedListNode_t x) {

}



void hashInsert(hashtable_t T, int key) {
        /* Creo nodo della lista */
        linkedListNode_t x;

        /* Inizializzazione del nodo */
        x.value = key;
        x.next = NULL;
        x.prev = NULL;

        /* Chiamo la funzione di hash */
        int i = hashFunc(key);

        /* Inserimento del nodo nella lista */
        listInsert(T.entry[i]->list->head, x);
}



/* ================ Fine metodi ================ */
//
/* ================ Dati Ausiliari ================ */

/* ================ Fine Dati Ausiliari ================ */
//
/** ================ Main Function ================ */
int main(int argc, char *argv[])
{
        /* Array di interi da inserire nella hash table */
        int a[] = {10, 5, 6, 4, 8, 9, 21, 45, 82, 70};



        return 0;
}
/* ================ End Main Function ================ */
