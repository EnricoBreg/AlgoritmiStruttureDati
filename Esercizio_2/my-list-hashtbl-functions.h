#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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