#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const unsigned int LIST_SIZE = 10;

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
        list->size = LIST_SIZE;
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
 */
void linkedListDelete(linkedList_t *list, linkedListNode_t *x)
{
        /* Rendo irragiungibile il nodo */
        if (x->prev != NULL)
        {
                x->prev->next = x->next;
        }
        else
        {
                /* Nel caso sia il primo nodo della lista */
                list->head = x->next;
        }

        if (x->next->prev != NULL)
        {
                x->next->prev = x->prev;
        }

        /* Nodo irraggiungibile, lo posso deallocare */
        free(x);
        return;
}

/**
 * @brief Free the linked list.
 * @param list Linked list to be freed.
 */
void linkedListFree(linkedList_t *list)
{
        
}

/* ============================= MAIN ============================= */
int main(int argc, char *argv[])
{
        unsigned int i;
        /* Array di interi da inserire nella hash table */
        int a[] = {10, 5, 6, 4, 8, 9, 21, 45, 82, 70};

        linkedList_t *list = createLinkedList();

        for (i = 0; i < LIST_SIZE; i++)
        {
                linkedListNode_t *node = createLinkedListNode(a[i]);
                linkedListInsert(list, node);
        }

        /* Valore da ricercare */
        int searched_value = 82;
        /* Ricerca nella lista */
        linkedListNode_t *searched_node = linkedListSearch(list, searched_value);
        printf("\nI'm searching the node...\n");
        if (searched_node != NULL)
        {
                printf("The linked list node with key %d exists.\n\n", searched_value);
        }
        else if (searched_node == NULL)
        {
                printf("The linked list node with key %d does not exist.\n\n", searched_value);
        }

        printf("\nYour linked list is:\n");
        linkedListPrint(list);
        printf("\n");

        printf("\nI'm deleting the selected node with key %d...\n", searched_value);
        linkedListDelete(list, searched_node);

        printf("\nI'm searching the node...\n");
        /* Provo a cercare il nodo eliminato per vedere se l'elimiazione funziona bene */
        searched_node = linkedListSearch(list, searched_value);
        if (searched_node != NULL)
        {
                printf("The linked list node with key %d exists.\n\n", searched_value);
        }
        else if (searched_node == NULL)
        {
                printf("The linked list node with key %d does not exist.\n\n", searched_value);
        }


        printf("\nYour linked list now is:\n");
        linkedListPrint(list);

        /* Termino */
        return 0;
}
