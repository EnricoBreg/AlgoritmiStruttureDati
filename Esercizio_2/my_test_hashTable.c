#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

const unsigned int LIST_SIZE = 3;

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
 */
void linkedListInsert(linkedList_t *list, linkedListNode_t *x)
{
        x->next = list->head;
        if (list->head != NULL)
        {
                list->head->prev = x;
        }
        list->head = x;
        x->prev = x;
        list->size += 1;
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
        if (x != NULL)
        {
                if (x->prev != NULL)
                {
                        x->prev->next = x->next;
                }
                else
                {
                        /* Nel caso sia il primo nodo della lista */
                        list->head = x->next;
                }

                if (x->next != NULL && x->next->prev != NULL)
                {
                        x->next->prev = x->prev;
                }

                /* Aggiorno la dimensione della lista */
                list->size -= 1;
        }
        /* Nodo irraggiungibile, lo posso deallocare */
        free(x);
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
        hashtable_t *hash_table = malloc(sizeof(hashtable_t));

        hash_table->size = s;
        hash_table->entry = (hashtableEntry_t **)malloc(sizeof(hashtableEntry_t *) * s);

        for (i = 0; i < hash_table->size; i++)
        {
                hashtableEntry_t *new_entry = malloc(sizeof(hashtableEntry_t));
                new_entry->list = createLinkedList();
                hash_table->entry[i] = new_entry;
        }

        /** Ritorno la tabella hash creata */
        return hash_table;
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
        linkedListNode_t *x = createLinkedListNode(v);
        unsigned int i = hashFunction(hashtbl, v);
        linkedListInsert(hashtbl->entry[i]->list, x);
        return;
}
/**
 * @brief Search for a value in the hashtable.
 * @param hashtbl The hashtable.
 * @param v Value to be searched.
 * @return Linked list node containing such value, if it exists; otherwise, NULL.
 */
/*linkedListNode_t *hashtableSearch(hashtable_t *hashtbl, const int v)
{
        return;
}*/

/**
 * @brief Delete value from hashtable.
 * @param hashtbl The hashtable.
 * @param x Linked list node to be deleted.
 */
/*void hashtableDelete(hashtable_t *hashtbl, linkedListNode_t *x)
{
}*/

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
/*bool hashtableTest()
{
        return;
}*/

/**
 * @brief Free hashtable.
 * @param hashtbl Hashtable to be freed.
 */
void hashtableFree(hashtable_t *hashtbl)
{
}

// ================================================================ //

/* ============================= MAIN ============================= */
int main(int argc, char *argv[])
{
        unsigned int i;
        /* Array di interi da inserire nella hash table */
        int ht_size = 10;
        int key = 20;
        int a[] = {10, 5, 6, 4, 8, 9, 21, 45, 82, 70};

        hashtable_t *hash_table;

        hash_table = createHashtable(ht_size);
        fprintf(stdout, "\nThe size of hash table is: %d\n", hash_table->size);

        /* Termino */
        return 0;
}
