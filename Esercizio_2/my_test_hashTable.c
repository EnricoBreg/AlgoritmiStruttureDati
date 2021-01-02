#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "my-list-hashtbl-functions.h"

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
/* ------------ End of linked list ------------ */

// ----- HASHTABLE ----- //

/**
 * @brief Hashtable entry data type.
 */
typedef struct hashtableEntry_t
{
        // Pointer to the list.
        struct linkedList_t *list;
} hashtableEntry_t;

/**
 * @brief Hashtable data type.
 */
typedef struct hashtable_t
{
        // Size in number of entries of the hashtable.
        unsigned int size;
        // Array of pointers to entries.
        struct hashtableEntry_t **entry;
} hashtable_t;

// ----- End of HASHTABLE ----- //

/* ========================== FUNZIONI ==========================*/
linkedListNode_t *createLinkedListNode(const int v)
{
        linkedListNode_t *node = malloc(sizeof(linkedListNode_t));
        node->next = NULL;
        node->prev = NULL;
        node->value = v;
        return node;
}

linkedList_t *createLinkedList(void)
{
        linkedList_t *list = malloc(sizeof(linkedList_t));
        list->head = NULL;
        list->size = 0;
        return list;
}

/**
 * @brief Insert linked list node in the head of the linked list.
 * @param list The linked list.
 * @param x Linked list node to be inserted.
 * La funzione inserisce in testa alla lista il nodo x passato come parametro
 */
void linkedListInsert(linkedList_t *list, linkedListNode_t *x)
{
        /** Il successore di x nella lista è la "vecchia" testa della lista */
        x->next = list->head;
        /** Se la lista non è vuota... */
        if (list->head != NULL) {
                /** ... il predecessore della "vecchia" testa della lista 
                 * diventa x */
                list->head->prev = x;
        }
        /** Assegno x come nuova testa della lista */
        list->head = x;
        /** Il campo prev della testa viene settato a NULL */
        x->prev = NULL;
        /** Aumento la dimensione della lista */
        list->size += 1;
        /** Terminazione */
        return;
}

/**
 * @brief Search for a value in the linked list.
 * @param list The linked list.
 * @param v Value to be searched for.
 * @return First linked list node containing such value, if it exists; otherwise, NULL.
*/
linkedListNode_t *linkedListSearch(linkedList_t *list, const int v)
{
        linkedListNode_t *x = list->head;
        while ((x != NULL) && (x->value != v))
        {
                /* Scorro la lista */
                x = x->next;
        }
        return x;
}

/**
 * @brief Print the linked list.
 * @param list Linked list to be printed.
 */
void linkedListPrint(linkedList_t *list)
{
        linkedListNode_t *x = list->head;
        while (x != NULL)
        {
                fprintf(stdout, "%d ", x->value);
                x = x->next;
        }
}

/**
 * @brief Delete a linked list node from linked list.
 * @param list The linked list.
 * @param x The linked list node to be deleted.
 * 
 * Per evitare errori di Segmentation Fault ho aggiunto un controllo per controllare
 * che il nodo dal eliminare dalla lista sia diverso da NULL
 */
void linkedListDelete(linkedList_t *list, linkedListNode_t *x)
{
        if (x == NULL) {
                /** Se il nodo da eliminare è NULL lo dealloco e termino*/
                free(x);
                return;
        }
        
        /** Assegnazione del nuovo valore al campo next del predeccessore */
        if (x->prev != NULL) {
                /** Caso di eliminazione di un nodo generico della lista */
                x->prev->next = x->next;
        }
        else {
                /** Caso di eliminazione del nodo in testa alla lista */
                list->head = x->next;
        }
        /** Assegnazione nuovo valore al campo prev del successore */
        if (x->next != NULL) {
                x->next->prev = x->prev;
        }
        /** Il nodo è irraggiungibile, lo posso deallocare */
        free(x);

        /** Diminuisco la dimensione della lista */
        list->size -= 1;

        /** Terminazione */
        return;
}

/**
 * @brief Free the linked list.
 * @param list Linked list to be freed.
 * L'eliminazione della lista viene gestita spostanndo il puntatore della testa sul nodo successivo
 * finché questo non diventa NULL o la dimensione della lista è != 0, Ogni nodo deferenziato dal
 * puntatore list viene poi eliminato usando linkedListDelete
 */
void linkedListFree(linkedList_t *list)
{
        linkedListNode_t *temp;
        while (list->head != NULL || list->size != 0)
        {
                /* salvo la testa della lista da eliminare */
                temp = list->head;
                //temp->prev = NULL;
                /* Assegno alla testa della lista il nodo successivo rendendo il nodo precedentemente
                 * head della lista non raggiungibile */
                list->head = list->head->next;
                linkedListDelete(list, temp);
        }
        /* Infine, dealloco il puntatore alla testa della lista */
        free(list);
        /* Terminazione */
        return;
}

// ================================================================= //(hashtableEntry_t)
// ----- HASHTABLE ----- //

/**
 * @brief Create a new hashtable.
 * @param s The size of the hashtable (i.e., the number of entries).
 * @return The created hashtable.
 */
hashtable_t *createHashtable(const unsigned int s)
{
        size_t i;
        /** Alloco la memoria per la tabella hash */
        hashtable_t *hashtbl = malloc(sizeof(hashtable_t));

        /** Assegno la dimensione della tabella hash */
        hashtbl->size = s;
        /** Alloco un array dinamico di dimensione s che conterrà i puntatori alle liste 
         * che conterranno le chiavi */
        hashtbl->entry = (hashtableEntry_t **)malloc(sizeof(hashtableEntry_t **) * s);

        for (i = 0; i < hashtbl->size; i++)
        {
                /** Alloco la new entry da essegnare alla posizione i-esima
                 * della lista */
                hashtableEntry_t *new_entry = (hashtableEntry_t*)malloc(sizeof(hashtableEntry_t*));
                /** Per la entry i-esima, creo una nuova lista collegata che 
                 * conterrà le chiavi */
                new_entry->list = createLinkedList();
                /* Assegno la new entry alla posizione i-esima */
                hashtbl->entry[i] = new_entry;
        }

        /** Ritorno la tabella hash creata */
        return hashtbl;
}

/**
 * @brief Hash function computing the key for a given integer.
 * @param hashtbl The hashtable needed to access the size of it.
 * @param v The integer for which the key must be computed.
 * @return The computed key.
 */
const unsigned int hashFunction(hashtable_t *hashtbl, const int v)
{
        return v % hashtbl->size;
}

/**
 * @brief Insert value in the hashtable.
 * @param hashtbl The hashtable.
 * @param v Value to be inserted.
 */
void hashtableInsert(hashtable_t *hashtbl, const int v)
{
        /* Creo il nodo per la lista che conterrà l'intero v */
        linkedListNode_t *x = createLinkedListNode(v);
        /** Attraverso la funzione hash ricavo la posizione di v
         * nella entry i-esima della tabella hash */
        unsigned int i = hashFunction(hashtbl, v);
        /** Inserisco il nodo creato in testa alla lista i-esima 
         * della tabella hash */
        linkedListInsert(hashtbl->entry[i]->list, x);
        /* Terminazione */
        return;
}
/**
 * @brief Search for a value in the hashtable.
 * @param hashtbl The hashtable.
 * @param v Value to be searched.
 * @return Linked list node containing such value, if it exists; otherwise, NULL.
 * 
 * La funzione ritorna il nodo cercato in caso di successo, altrimenti ritorna
 * NULL se il valore cercato non è presente nella tabella hash
 */
linkedListNode_t *hashtableSearch(hashtable_t *hashtbl, const int v)
{
        /** Creo un puntatore al nodo da cercare */
        linkedListNode_t *searched_node = NULL;
        /** La variabile i rappresenta la entry i-esima della tabella hash
         * dove cercare la chiave v passata */
        unsigned int i = hashFunction(hashtbl, v);
        /** Ricerca dalla chiave v nella i-esima lista della tabella hash */
        searched_node = linkedListSearch(hashtbl->entry[i]->list, v);
        /** Ritorno il nodo cercato, se la funzione di ricerca non ha ritornato nulla
         * il nodo vale NULL come valore inizialmente assegnato */
        return searched_node;
}

/**
 * @brief Delete value from hashtable.
 * @param hashtbl The hashtable.
 * @param x Linked list node to be deleted.
 */
void hashtableDelete(hashtable_t *hashtbl, linkedListNode_t *x)
{
        unsigned int i;

        /** Questa scelta è stata fatta in quanto la operazione di eliminazione
         * viene verosimilmente collegata ad una operazione di ricerca.
         * Se il nodo cercato non esiste, allora non ha senso eliminarlo.
         * Se non fosse stata fatta tale scelta con molta probabilità si incorre
         * in un Segmentation Fault. */
        if (x == NULL)
        {
                /** Il valore del linkedListNode_t x è NULL, cioè non esiste e
                 * non ha senso proseguire */
                return;
        }

        /** Il nodo da eliminare è diverso da NULL e posso proseguire
         * con la cancellazione */
        i = hashFunction(hashtbl, x->value);

        /** Eseguo la cancellazione sulla entry i-esima della tabella hash */
        linkedListDelete(hashtbl->entry[i]->list, x);

        /** Terminazione*/
        return;
}

/**
 * @brief Print the hashtable.
 * @param hashtbl Hashtable to be printed.
 */
void hashtablePrint(hashtable_t *hashtbl)
{
        for (int i = 0; i < hashtbl->size; i++)
        {
                fprintf(stdout, "%d => ", i);
                linkedListPrint(hashtbl->entry[i]->list);
                fprintf(stdout, "\n");
        }
}

/**
 * @brief Test hashtable if it is correctly implemented.
 * @return True if it is correct; otherwise, false.
 */
bool hashtableTest(hashtable_t *hashtbl)
{
        unsigned int i;
        int hashfvalue;
        hashtable_t *tmptbl = hashtbl;
        linkedListNode_t *htelist = NULL;

        for (i = 0; i < tmptbl->size; i++) {
                htelist = tmptbl->entry[i]->list->head;
                while(htelist != NULL) {
                        hashfvalue = hashFunction(tmptbl, htelist->value);
                        if (hashfvalue != i) {
                                return false;
                        }
                        /** Scorri la lista */
                        htelist = htelist->next;
                }
                htelist = NULL;
        }

        return true;
}

/**
 * @brief Free hashtable.
 * @param hashtbl Hashtable to be freed.
 */
void hashtableFree(hashtable_t *hashtbl)
{
        unsigned int i;
        
        /** Per ogni entri uso linkedListFree per deallocare l'intera
         * lista della i-esima entry
        */
        for(i = 0; i < hashtbl->size; i++) {
                linkedListFree(hashtbl->entry[i]->list);
        }
        /** Una volta terminata la deallocazione di tutte le liste 
         * posso deallocare anche l'array dinamico delle entry della tabella hash */
        free(hashtbl);

        /** Terminazione */
        return;
}

// ================================================================ //

/* ============================= MAIN ============================= */
int main(int argc, char *argv[])
{
        unsigned int i;
        /* Array di interi da inserire nella hash table */
        int ht_size = 10;
        int a[] = {10, 5, 6, 4, 8, 9, 21, 45, 82, 70};

        hashtable_t *hashtbl = NULL;

        hashtbl = createHashtable(ht_size);
        fprintf(stdout, "\nThe size of hash table is: %d\n", hashtbl->size);

        fprintf(stdout, "\nProva inserimento array in tabella hash...\n");
        for (i = 0; i < hashtbl->size; i++)
        {
                hashtableInsert(hashtbl, a[i]);
        }

        fprintf(stdout, "\nStampo la tabella hash...\n");
        hashtablePrint(hashtbl);

        fprintf(stdout, "\nProva ricerca valore nella tabella hash...\n");
        linkedListNode_t *node = hashtableSearch(hashtbl, a[2]);

        if (node != NULL)
        {
                fprintf(stderr, "This value is in the table\n");
        }
        else
        {
                fprintf(stdout, "This value is not in the table\n");
        }

        hashtableDelete(hashtbl, node);

        hashtablePrint(hashtbl);


        /** Prova hashtable check */
        bool isHashTable;
        if ((isHashTable = hashtableTest(hashtbl)) == false) {
                fprintf(stderr, "\nNon è una hash table\n");
        } else {
                fprintf(stderr, "\nè una hash table\n");
        }

        hashtableFree(hashtbl);        

        /* Termino */
        return 0;
}
