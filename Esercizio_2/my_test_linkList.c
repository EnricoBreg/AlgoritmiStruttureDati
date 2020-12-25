#include <stdio.h>
#include <stdlib.h>


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


int main(int argc, char *argv[])
{
        /* Array di interi da inserire nella hash table */
        int a[] = {10, 5, 6, 4, 8, 9, 21, 45, 82, 70};

        


        return 0;
}

