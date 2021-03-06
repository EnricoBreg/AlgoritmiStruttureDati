/**
 * @brief Problem 2, Laboratory of Algorithms and Data Structures.
 * @author SCIAVICCO Guido (guido.sciavicco@unife.it)
 * @author STAN Ionel Eduard (ioneleduard.stan@unife.it)
 * @version Teacher
 */

// ##### LIBRARIES ##### //

// Standard input-output library (e.g., fprintf).
#include <stdio.h>
// Time library (e.g., time, clock()).
#include <time.h>
// Standard library (e.g., rand, srand).
#include <stdlib.h>
// Boolean library (e.g., bool).
#include <stdbool.h>
// String library (e.g., strcmp)
#include <string.h>

// ##### End of LIBRARIES ##### //

// ##### DATA STRUCTURES ##### //

// ----- LINKED LIST ----- //

/**
 * @brief Linked list node data type.
 */
typedef struct linkedListNode_t {
    // Value contained in the node.
    int value;
    // Pointer to next node.
    struct linkedListNode_t* next;
    // Pointer to previous node.
    struct linkedListNode_t* prev;
} linkedListNode_t;

/**
 * @brief Linked list data type.
 */
typedef struct linkedList_t {
    // Size in number of nodes of the list.
    unsigned int size;
    // Pointer to the head node of the list.
    struct linkedListNode_t* head;
} linkedList_t;

// ----- End of LINKED LIST ----- //

// ----- HASHTABLE ----- //

/**
 * @brief Hashtable entry data type.
 */
typedef struct hashtableEntry_t {
    // Pointer to the list.
    struct linkedList_t* list;
} hashtableEntry_t;

/**
 * @brief Hashtable data type.
 */
typedef struct hashtable_t {
    // Size in number of entries of the hashtable.
    unsigned int size;
    // Array of pointers to entries.
    struct hashtableEntry_t** entry;
} hashtable_t;

// ----- End of HASHTABLE ----- //

// ----- RED BLACK TREE (RBT) ----- //

/**
 * @brief RBT node data type.
 */
typedef struct rbtNode_t {
    // Value contained in the node.
    int value;
    // Color of the node.
    char color;
    // Pointer to the parent node.
    struct rbtNode_t* parent;
    // Pointer to the left node.
    struct rbtNode_t* left;
    // Pointer to the right node.
    struct rbtNode_t* right;
} rbtNode_t;

/**
 * @brief RBT data type.
 */
typedef struct rbt_t {
    // Size in number of nodes of the RBT.
    unsigned int size;
    // Pointer to the root node.
    struct rbtNode_t* root;
    // Pointer to RBT NIL node.
    struct rbtNode_t* nil;
} rbt_t;

/**
 * @brief RBT test data structure.
 */
typedef struct rbtTestStructure_t {
    // Array that contains the in order visit values of the RBT.
    int* A;
    // Current index of the array.
    int index;
} rbtTestStructure_t;

// ----- End of RBT ----- //

// ----- AUXILIARY DATA STRUCTURES ----- //

/**
 * @brief Enumeration data type for the output.
 */
typedef enum outputEnum_t {
    ONCONSOLE,  // On console.
    ONFILE      // On file.
} outputEnum_t;

// ----- End of AUXILIARY DATA STRUCTURES ----- //

// ##### End of DATA STRUCTURES ##### //

// ##### GLOBAL VARIABLES ###### //

// Random seed (important for reproducibility).
time_t RANDOM_SEED = 20;
// Maximum random number allowed.
const unsigned int MAX_RANDOM_NUMBER = 10000000;
// Minimum number of operations.
const unsigned int MIN_OPERATIONS = 100;
// Maximum number of operations.
const unsigned int MAX_OPERATIONS = 2000;
// Step of the experiment.
const unsigned int STEP = 100;
// Number of experiments.
const unsigned int NUM_EXPERIMENTS = 50;
// Percentage of insert operations.
const unsigned int PERCENTAGE_INSERTIONS = 40;
// Size of the hashtable.
const unsigned int NUM_ENTRIES = 59;
// Test data structures?
const bool TEST_DATA_STRUCTURES = true;
// Number of elements for testing.
const unsigned int NUM_ELEMENTS_FOR_TEST = 1000;
// Output type.
const outputEnum_t outputType = ONFILE;
// Output pointer (for printing).
FILE* outputPointer;

// ##### End of GLOBAL VARIABLES #####

// ##### PROTOTYPES OF THE FUNCTIONS ##### //

// ----- LINKED LIST ----- //

/**
 * @brief Create a new linked list node.
 * @param Value that the linked list node should contain.
 * @return Created linked list node.
 */
linkedListNode_t* createLinkedListNode(const int);

/**
 * @brief Create a new linked list.
 * @return Created linked list.
 */
linkedList_t* createLinkedList();

/**
 * @brief Insert linked list node in the head of the linked list.
 * @param The linked list.
 * @param Linked list node to be inserted.
 */
void linkedListInsert(linkedList_t*, linkedListNode_t*);

/**
 * @brief Search for a value in the linked list.
 * @param The linked list.
 * @param Value to be searched for.
 * @return First linked list node containing such value, if it exists; otherwise, NULL.
*/
linkedListNode_t* linkedListSearch(linkedList_t*, const int);

/**
 * @brief Delete a linked list node from linked list.
 * @param The linked list.
 * @param The linked list node to be deleted.
 */
void linkedListDelete(linkedList_t*, linkedListNode_t*);

/**
 * @brief Print the linked list.
 * @param Linked list to be printed.
 */
void linkedListPrint(linkedList_t*);

/**
 * @brief Free the linked list.
 * @param Linked list to be freed.
 */
void linkedListFree(linkedList_t*);

// ----- End of LINKED LIST ----- //

// ----- HASHTABLE ----- //

/**
 * @brief Create a new hashtable.
 * @param The size of the hashtable (i.e., the number of entries).
 * @return The created hashtable.
 */
hashtable_t* createHashtable(const unsigned int);

/**
 * @brief Hash function computing the key for a given integer.
 * @param The hashtable needed to access the size of it.
 * @param The integer for which the key must be computed.
 * @return The computed key.
 */
const unsigned int hashFunction(hashtable_t*, const int);

/**
 * @brief Insert value in the hashtable.
 * @param The hashtable.
 * @param Value to be inserted.
 */
void hashtableInsert(hashtable_t*, const int);

/**
 * @brief Search for a value in the hashtable.
 * @param The hashtable.
 * @param Value to be searched.
 * @return Linked list node containing such value, if it exists; otherwise, NULL.
 */
linkedListNode_t* hashtableSearch(hashtable_t*, const int);

/**
 * @brief Delete value from hashtable.
 * @param The hashtable.
 * @param Linked list node to be deleted.
 */
void hashtableDelete(hashtable_t*, linkedListNode_t*);

/**
 * @brief Print the hashtable.
 * @param Hashtable to be printed.
 */
void hashtablePrint(hashtable_t*);

/**
 * @brief Test hashtable implementation.
 * @return True if it is correct; otherwise, false.
 */
bool hashtableTest();

/**
 * @brief Free hashtable.
 * @param Hashtable to be freed.
 */
void hashtableFree(hashtable_t*);

// ----- End of HASHTABLE ----- //

// ----- RBT ----- //

/**
 * @brief Create new RBT node.
 * @param Value that the RBT node should contain.
 * @return Created RBT node.
 */
rbtNode_t* createRbtNode(const int);

/**
 * @brief Create new RBT.
 * @return Created RBT.
 */
rbt_t* createRbt();

/**
 * @brief Left rotate operation.
 * @param The RBT.
 * @param The RBT node to rotate on.
 */
void rbtLeftRotate(rbt_t*, rbtNode_t*);
/**
 * @brief Right rotate operation.
 * @param The RBT.
 * @param The RBT node to rotate on.
 */
void rbtRightRotate(rbt_t*, rbtNode_t*);

/**
 * @brief Insert RBT node in th RBT.
 * @param The RBT.
 * @param The RBT node to be inserted.
 */
void rbtInsert(rbt_t*, rbtNode_t*);

/**
 * @brief Fixup function for RBT insertion.
 * @param The RBT the be fixed.
 * @param The initial RBT node to be fixed.
 */
void rbtInsertFixup(rbt_t*, rbtNode_t*);

/**
 * @brief Search for a value in the RBT.
 * @param The RBT.
 * @param Value to be searched.
 * @return RBT node containing the value, if it exists; otherwise, NULL.
 */
rbtNode_t* rbtSearch(rbt_t*, const int);

/**
 * @brief Print RBT in order.
 * @param RBT to be printed.
 * @param RBT node to be printed.
 */
void rbtInOrder(rbt_t*, rbtNode_t*);

/**
 * @brief Test RBT implementation.
 * @return True if it is correct; otherwise, false.
 */
bool rbtTest();

/**
 * @brief Check if the tree is actually a RBT.
 * @param Tree to be checked.
 * @return True if it is; otherwise, false.
 */
bool isRbt(rbt_t*);

/**
 * @brief Function that checks if the tree has the BST property (i.e., x->left->value < x->value <= x->right->value, for all x).
 * @param Tree to be checked.
 * @return True if it is; otherwise, false.
 */
bool rbtHasBstProperty(rbt_t*);

/**
 * @brief Utility function for checking if the tree has the BST property.
 * @param Tree to be checked.
 * @param Current RBT node.
 * @param RBT test data structure.
 */
void rbtHasBstPropertyUtil(rbt_t*, rbtNode_t*, rbtTestStructure_t*);

/**
 * @brief Function that computes the black height of the RBT.
 * @param The RBT.
 * @param Current RBT node.
 * @return Black height if all paths have the same black height; otherwise, -1.
 */
int rbtComputeBlackHeight(rbt_t*, rbtNode_t*);

/**
 * @brief Free RBT nodes.
 * @param RBT whose nodes must be freed.
 * @param RBT node to be freed.
 */
void rbtFreeNodes(rbt_t*, rbtNode_t*);

/**
 * @brief Free RBT.
 * @param RBT to be freed.
 */
void rbtFree(rbt_t*);

// ----- End of RBT ----- //

// ----- AUXILIARY FUNCTIONS ----- //
/**
 * @brief Generate a collection of random numbers.
 * @param Array of random numbers.
 * @param Size of the array.
 */
void generateRandomArray(int*, const int);

/**
 * @brief Unit test: check if the input array is sorted.
 * @param Array to be checked if sorted.
 * @param Size of the array.
 * @return True if it is sorted; otherwise, false
 */
bool isSorted(const int*, const int);

// ----- End of AUXILIARY FUNCTIONS ----- //

// ----- CORE FUNCTIONS ----- //

/**
 * @brief Function that does the experiment.
 * @param Array of random numbers.
 * @param Number of insertion operations.
 * @param Number of search operations.
 * @param Data structure to be used. The possible values are:
 * @return Elapsed time for the experiment.
 */
clock_t doExperiment(int*, const unsigned int, const unsigned int, char*);

// ----- End of CORE FUNCTIONS ----- //

// ##### End of PROTOTYPES OF THE FUNCTIONS ##### //

int main(int argc, char *argv[]) {

    // Random seed initialization.
    srand(RANDOM_SEED);
    // Elapsed time for hashtable.
    clock_t timeHashtable = 0;
    // Elapsed time for RBT.
    clock_t timeRbt = 0;
    // Number of insert operations.
    unsigned int numInsertions = 0;
    // Number of search operations.
    unsigned int numSearches = 0;

    // What is the outputPointer?
    if (outputType == ONCONSOLE || outputType == ONFILE) {
        // On console.
        if (outputType== ONCONSOLE) outputPointer = stdout;
        // On file.
        else {
            // Open file.
            outputPointer = fopen("results.txt", "w");
            // Have we opened the file?
            if (outputPointer == NULL) {
                fprintf(stderr, "ERROR: The outputPointer has not been created\n");
                exit(-1);
            }
        }
    }
    // Error
    else {
        fprintf(stderr, "ERROR: The outputType can be only ONCONSOLE or ONFILE\n");
        exit(-1);
    }

    // Print the header, only if it is on console.
    if (outputType == ONCONSOLE) {
        fprintf(outputPointer, "+-----------------------------+---------------------+---------------------+\n");
        fprintf(outputPointer, "| Operations - %%I & %%S        | Hashtable - %-5d   | Red Black Tree      |\n", NUM_ENTRIES);
        fprintf(outputPointer, "+-----------------------------+---------------------+---------------------+\n");
    }

    // For each number of operations in the interval [MIN_OPERATIONS, MAX_OPERATIONS] with STEP
    for (int numOps=MIN_OPERATIONS; numOps<=MAX_OPERATIONS; numOps+=STEP) {
        // Reset the times.
        timeHashtable = timeRbt = 0;
        // For each experiment
        for (int exper=1; exper<=NUM_EXPERIMENTS; exper++) {

            // Compute the number of insert operations.
            numInsertions = numOps*PERCENTAGE_INSERTIONS/100;
            // Compute the number of search operations.
            numSearches = numOps-numInsertions;
            // Allocate numInsertions memory cells for the array of random numbers.
            int* randomArray = malloc(numInsertions*sizeof(int));
            // Fill-in the array with random numbers.
            generateRandomArray(randomArray, numInsertions);
            // Hashtable experiment.
            timeHashtable += doExperiment(randomArray, numInsertions, numSearches, "hashtable");
            // RBT experiment.
            timeRbt += doExperiment(randomArray, numInsertions, numSearches, "rbt");
            // Free the array of random numbers.
            free(randomArray);
        }
        // Printing the (sample mean as) result. Use TAB (\t) on file.
        if (outputType == ONCONSOLE)
            fprintf(outputPointer, "| %15d - %-3d & %-3d | %19f | %19f |\n",
                numOps,
                PERCENTAGE_INSERTIONS,
                100-PERCENTAGE_INSERTIONS,
                (float) timeHashtable/NUM_EXPERIMENTS,
                (float) timeRbt/NUM_EXPERIMENTS);
        else
            fprintf(outputPointer, "%d \t%f \t%f \n",
                numOps,
                (float) timeHashtable/NUM_EXPERIMENTS,
                (float) timeRbt/NUM_EXPERIMENTS);
    }

    // Print the ending part, only if it is on console.
    if (outputType == ONCONSOLE) {
        fprintf(outputPointer, "+-----------------------------+---------------------+---------------------+\n");
        fprintf(outputPointer, "| Legend:                                                                 |\n");
        fprintf(outputPointer, "|                                                                         |\n");
        fprintf(outputPointer, "| %%I: Percentage of insertion operations                                  |\n");
        fprintf(outputPointer, "| %%S: Percentage of search operations                                     |\n");
        fprintf(outputPointer, "|                                                                         |\n");
        fprintf(outputPointer, "| The number near \"Hashtable\" is the number of entries in the hashtable   |\n");
        fprintf(outputPointer, "+-------------------------------------------------------------------------+\n");
    }

    if (TEST_DATA_STRUCTURES) {
        fprintf(outputPointer, "| Hashtable implementation: %-12s                                  |\n", hashtableTest() ? "correct" : "not correct");
        fprintf(outputPointer, "| Red black tree implementation: %-12s                             |\n", rbtTest() ? "correct" : "not correct");
        fprintf(outputPointer, "+-------------------------------------------------------------------------+\n");
    }

    // Return 0.
    return 0;
}

// ##### IMPLEMENTATION OF THE FUNCTIONS ##### //

// ----- LINKED LIST ----- //

/**
 * @brief Create a new linked list node.
 * @param v Value that the linked list node should contain.
 * @return Created linked list node.
 */
linkedListNode_t* createLinkedListNode(const int v) {
    return;
}

/**
 * @brief Create a new linked list.
 * @return Created linked list.
 */
linkedList_t* createLinkedList() {
    return;
}

/**
 * @brief Insert linked list node in the head of the linked list.
 * @param list The linked list.
 * @param x Linked list node to be inserted.
 */
void linkedListInsert(linkedList_t* list, linkedListNode_t* x) {
}

/**
 * @brief Search for a value in the linked list.
 * @param list The linked list.
 * @param v Value to be searched for.
 * @return First linked list node containing such value, if it exists; otherwise, NULL.
*/
linkedListNode_t* linkedListSearch(linkedList_t* list, const int v) {
    return;
}

/**
 * @brief Delete a linked list node from linked list.
 * @param list The linked list.
 * @param x The linked list node to be deleted.
 */
void linkedListDelete(linkedList_t* list, linkedListNode_t* x) {
}

/**
 * @brief Print the linked list.
 * @param list Linked list to be printed.
 */
void linkedListPrint(linkedList_t* list) {
    linkedListNode_t* x = list->head;
    while (x) {
        fprintf(stdout, "%d ", x->value);
        x = x->next;
    }
}

/**
 * @brief Free the linked list.
 * @param list Linked list to be freed.
 */
void linkedListFree(linkedList_t* list) {
}

// ----- End of LINKED LIST ----- //

// ----- HASHTABLE ----- //

/**
 * @brief Create a new hashtable.
 * @param s The size of the hashtable (i.e., the number of entries).
 * @return The created hashtable.
 */
hashtable_t* createHashtable(const unsigned int s) {
    return;
}

/**
 * @brief Hash function computing the key for a given integer.
 * @param hashtbl The hashtable needed to access the size of it.
 * @param v The integer for which the key must be computed.
 * @return The computed key.
 */
const unsigned int hashFunction(hashtable_t* hashtbl, const int v) {
    return v % hashtbl->size;
}

/**
 * @brief Insert value in the hashtable.
 * @param hashtbl The hashtable.
 * @param v Value to be inserted.
 */
void hashtableInsert(hashtable_t* hashtbl, const int v) {
}

/**
 * @brief Search for a value in the hashtable.
 * @param hashtbl The hashtable.
 * @param v Value to be searched.
 * @return Linked list node containing such value, if it exists; otherwise, NULL.
 */
linkedListNode_t* hashtableSearch(hashtable_t* hashtbl, const int v) {
    return;
}

/**
 * @brief Delete value from hashtable.
 * @param hashtbl The hashtable.
 * @param x Linked list node to be deleted.
 */
void hashtableDelete(hashtable_t* hashtbl, linkedListNode_t* x) {
}

/**
 * @brief Print the hashtable.
 * @param hashtbl Hashtable to be printed.
 */
void hashtablePrint(hashtable_t* hashtbl) {
    for (int i=0; i<hashtbl->size; i++) {
        fprintf(stdout, "%d => ", i);
        linkedListPrint(hashtbl->entry[i]->list);
        fprintf(stdout, "\n");
    }
}

/**
 * @brief Test hashtable if it is correctly implemented.
 * @return True if it is correct; otherwise, false.
 */
bool hashtableTest() {
    return;
}

/**
 * @brief Free hashtable.
 * @param hashtbl Hashtable to be freed.
 */
void hashtableFree(hashtable_t* hashtbl) {
}

// ----- End of HASHTABLE ----- //

// ----- RBT ----- //

/**
 * @brief Create new RBT node.
 * @param v Value that the RBT node should contain.
 * @return Created RBT node.
 */
rbtNode_t* createRbtNode(const int v) {
}

/**
 * @brief Create new RBT.
 * @return Created RBT.
 */
rbt_t* createRbt() {
}

/**
 * @brief Left rotate operation.
 * @param rbt The RBT.
 * @param x The RBT node to rotate on.
 */
void rbtLeftRotate(rbt_t* rbt, rbtNode_t* x) {
}

/**
 * @brief Right rotate operation.
 * @param rbt The RBT.
 * @param x The RBT node to rotate on.
 */
void rbtRightRotate(rbt_t* rbt, rbtNode_t* x) {
}

/**
 * @brief Insert RBT node in th RBT.
 * @param rbt The RBT.
 * @param z The RBT node to be inserted.
 */
void rbtInsert(rbt_t* rbt, rbtNode_t* z) {
}

/**
 * @brief Fixup function for RBT insertion.
 * @param rbt The RBT the be fixed.
 * @param z The initial RBT node to be fixed.
 */
void rbtInsertFixup(rbt_t* rbt, rbtNode_t* z) {
}

/**
 * @brief Search for a value in the RBT.
 * @param rbt The RBT.
 * @param v Value to be searched.
 * @return RBT node containing the value, if it exists; otherwise, NULL.
 */
rbtNode_t* rbtSearch(rbt_t* rbt, const int v) {
}

/**
 * @brief Print RBT in order.
 * @param rbt RBT to be printed.
 * @param x RBT node to be printed.
 */
void rbtInOrder(rbt_t* rbt, rbtNode_t* x) {
    if (x != rbt->nil) {
        rbtInOrder(rbt, x->left);
        printf("%d ", x->value);
        rbtInOrder(rbt, x->right);
    }
}

/**
 * @brief Test RBT if it is correctly implemented.
 * @return True if it is correct; otherwise, false.
 */
bool rbtTest() {
    return;
}

/**
 * @brief Check if the tree is actually a RBT.
 * @param rbt Tree to be checked.
 * @return True if it is; otherwise, false.
 */
bool isRbt(rbt_t* rbt) {
}

/**
 * @brief Function that checks if the tree has the BST property (i.e., x->left->value < x->value <= x->right->value, for all x).
 * @param rbt Tree to be checked.
 * @return True if it is; otherwise, false.
 */
bool rbtHasBstProperty(rbt_t* rbt) {
return;
}

/**
 * @brief Utility function for checking if the tree has the BST property.
 * @param rbt Tree to be checked.
 * @param x Current RBT node.
 * @param rbtTestStructure RBT test data structure.
 */
void rbtHasBstPropertyUtil(rbt_t* rbt, rbtNode_t* x, rbtTestStructure_t* rbtTestStructure) {
}

/**
 * @brief Function that computes the black height of the RBT.
 * @param rbt The RBT.
 * @param x Current RBT node.
 * @return Black height if all paths have the same black height; otherwise, -1.
 */
int rbtComputeBlackHeight(rbt_t* rbt, rbtNode_t* x) {
}

/**
 * @brief Free RBT nodes.
 * @param T RBT whose nodes must be freed.
 * @param x RBT node to be freed.
 */
void rbtFreeNodes(rbt_t* T, rbtNode_t* x) {
}

/**
 * @brief Free RBT.
 * @param T RBT to be freed.
 */
void rbtFree(rbt_t* T) {

}

// ----- End of RBT ----- //

// ----- AUXILIARY FUNCTIONS ----- //

/**
 * @brief Generate a collection of random numbers.
 * @param A Array of random numbers.
 * @param n Size of the array.
 */
void generateRandomArray(int* A, const int n) {
    // For each i in 0..n-1, generate a random number.
    for (int i = 0; i < n; i++) A[i] = rand() % MAX_RANDOM_NUMBER;
}

/**
 * @brief Unit test: check if the input array is sorted.
 * @param A Array to be checked if sorted.
 * @param n Size of the array.
 * @return True if it is sorted; otherwise, false
 */
bool isSorted(const int* A, const int n) {
    // For each i in 0..n-2, if the current element is greater than the next one,
    // then it is unsorted.
    for (int i = 0; i < n-1; i++) if (A[i] > A[i+1]) return false;
    // Otherwise it is.
    return true;
}

// ----- End of AUXILIARY FUNCTIONS ----- //

// ----- CORE FUNCTIONS ----- //

/**
 * @brief Function that does the experiment.
 * @param randomArray Array of random numbers.
 * @param numInsertions Number of insertion operations.
 * @param numSearches Number of search operations.
 * @param dataStructure Data structure to be used. The possible values are: hashtable and rbt.
 * @return Elapsed time for the experiment.
 */
clock_t doExperiment(int* randomArray, const unsigned int numInsertions, const unsigned int numSearches, char* dataStructure) {
    return;
}

// ----- End of CORE FUNCTIONS ----- //

// ##### End of IMPLEMENTATION OF THE FUNCTIONS ##### //
