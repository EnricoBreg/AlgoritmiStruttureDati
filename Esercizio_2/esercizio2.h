#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// -------------- Linked List -------------- //
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

// -------------- Hash Table -------------- //

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

// -------------- Red Black Tree -------------- //
/**
 * @brief RBT node data type.
 */
typedef struct rbtNode_t
{
    // Value contained in the node.
    int value;
    // Color of the node.
    char color;
    // Pointer to the parent node.
    struct rbtNode_t *parent;
    // Pointer to the left node.
    struct rbtNode_t *left;
    // Pointer to the right node.
    struct rbtNode_t *right;
} rbtNode_t;

/**
 * @brief RBT data type.
 */
typedef struct rbt_t
{
    // Size in number of nodes of the RBT.
    unsigned int size;
    // Pointer to the root node.
    struct rbtNode_t *root;
    // Pointer to RBT NIL node.
    struct rbtNode_t *nil;
} rbt_t;

/**
 * @brief RBT test data structure.
 */
typedef struct rbtTestStructure_t
{
    // Array that contains the in order visit values of the RBT.
    int *A;
    // Current index of the array.
    int index;
} rbtTestStructure_t;

// -------------- END DATA STRUCTURES -------------- //

// =================================================== //
// -------------- FUNCTIONS -------------- //
//
// ----------- Linked list & Hash Table ----------- //
/**
 * @brief Crea un nuovo nodo per la lista collegata
 * @param v chiave da inserire nel nodo
 * @return ritorna un puntatore ad un struttura linkedListNode_t
*/

linkedListNode_t *createLinkedListNode(const int v);
/**
 * @brief Alloca la memoria per il puntatore alla testa della lista
 * @return ritorna un puntatore ad una struttura linkedList_t
*/
linkedList_t *createLinkedList(void);

/**
 * @brief Insert linked list node in the head of the linked list.
 * @param list The linked list.
 * @param x Linked list node to be inserted.
 * La funzione inserisce in testa alla lista il nodo x passato come parametro
 */
void linkedListInsert(linkedList_t *list, linkedListNode_t *x);

/**
 * @brief Search for a value in the linked list.
 * @param list The linked list.
 * @param v Value to be searched for.
 * @return First linked list node containing such value, if it exists; otherwise, NULL.
*/
linkedListNode_t *linkedListSearch(linkedList_t *list, const int v);

/**
 * @brief Print the linked list.
 * @param list Linked list to be printed.
 */
void linkedListPrint(linkedList_t *list);

/**
 * @brief Delete a linked list node from linked list.
 * @param list The linked list.
 * @param x The linked list node to be deleted.
 * 
 * Per evitare errori di Segmentation Fault ho aggiunto un controllo per controllare
 * che il nodo dal eliminare dalla lista sia diverso da NULL
 */
void linkedListDelete(linkedList_t *list, linkedListNode_t *x);

/**
 * @brief Free the linked list.
 * @param list Linked list to be freed.
 * L'eliminazione della lista viene gestita spostanndo il puntatore della testa sul nodo successivo
 * finché questo non diventa NULL o la dimensione della lista è != 0, Ogni nodo deferenziato dal
 * puntatore list viene poi eliminato usando linkedListDelete
 */
void linkedListFree(linkedList_t *list);

/**
 * @brief Create a new hashtable.
 * @param s The size of the hashtable (i.e., the number of entries).
 * @return The created hashtable.
 */
hashtable_t *createHashtable(const unsigned int s);

/**
 * @brief Hash function computing the key for a given integer.
 * @param hashtbl The hashtable needed to access the size of it.
 * @param v The integer for which the key must be computed.
 * @return The computed key.
 */
const unsigned int hashFunction(hashtable_t *hashtbl, const int v);

/**
 * @brief Insert value in the hashtable.
 * @param hashtbl The hashtable.
 * @param v Value to be inserted.
 */
void hashtableInsert(hashtable_t *hashtbl, const int v);

/**
 * @brief Search for a value in the hashtable.
 * @param hashtbl The hashtable.
 * @param v Value to be searched.
 * @return Linked list node containing such value, if it exists; otherwise, NULL.
 * 
 * La funzione ritorna il nodo cercato in caso di successo, altrimenti ritorna
 * NULL se il valore cercato non è presente nella tabella hash
 */
linkedListNode_t *hashtableSearch(hashtable_t *hashtbl, const int v);

/**
 * @brief Delete value from hashtable.
 * @param hashtbl The hashtable.
 * @param x Linked list node to be deleted.
 */
void hashtableDelete(hashtable_t *hashtbl, linkedListNode_t *x);

/**
 * @brief Print the hashtable.
 * @param hashtbl Hashtable to be printed.
 */
void hashtablePrint(hashtable_t *hashtbl);

/**
 * @brief Test hashtable if it is correctly implemented.
 * @return True if it is correct; otherwise, false.
 */
bool isHashTable(hashtable_t *hashtbl);

/**
 * @brief Free hashtable.
 * @param hashtbl Hashtable to be freed.
 */
void hashtableFree(hashtable_t *hashtbl);

// ------------ Red Black Tree ------------ //
/**
 * @brief Alloca la memoria necessaria per la struttura dati del tipo rbtNode_t.
 * @param Value that the RBT node should contain.
 * @return Created RBT node.
 */
rbtNode_t *createRbtNode(const int key);

/**
 * @brief Alloca la memoria necessaria per la struttura dati del tipo rbt_t.
 * @return Created RBT.
 */
rbt_t *createRbt(void);

/**
 * @brief Left rotate operation.
 * @param t RBT.
 * @param x RBT node to rotate on.
 */
void rbtLeftRotate(rbt_t *t, rbtNode_t *x);
/**
 * @brief Right rotate operation.
 * @param The RBT.
 * @param The RBT node to rotate on.
 */
void rbtRightRotate(rbt_t *t, rbtNode_t *x);

/**
 * @brief Inserimento di un nodo z nell'albero t.
 * @param The RBT.
 * @param The RBT node to be inserted.
 */
void rbtInsert(rbt_t *t, rbtNode_t *z);

/**
 * @brief Sistema eventuali violazioni delle proprietà 2 e 4 dell'rbt.
 * @param t RBT the be fixed.
 * @param z initial RBT node to be fixed.
 */
void rbtInsertFixup(rbt_t *t, rbtNode_t *z);
/**
 * @brief Sistema le relazioni padre e figlio destro ed eventuali sbilanciamenti dell'albero
 * @param t
 * @param z
*/
void rbtInsertFixupLeft(rbt_t *t, rbtNode_t *z);
/**
 * @brief Sistema le relazioni padre e figlio sinistro ed eventuali sbilanciamenti dell'albero
 * @param t
 * @param z
*/
void rbtInsertFixupRight(rbt_t *t, rbtNode_t *z);

/**
 * @brief Ricerca del massimo 
 * @param rbt puntatore a rbt
 * @param node puntatore ad un nodo rbt
 * @return nodoo con la chiave massima
 */
rbtNode_t *rbtMaximum(rbt_t *rbt, rbtNode_t *tnode);

/**
 * @brief Ricerca del minimo 
 * @param rbt puntatore a rbt
 * @param node puntatore ad un nodo rbt
 * @return nodoo con la chiave minore
 */
rbtNode_t *rbtMinimum(rbt_t *rbt, rbtNode_t *tnode);

/**
 * @brief Search recursively for a value in the RBT.
 * @param t puntatore alla struttura rbt_t.
 * @param t_rdx puntatore alla radice dell'albero
 * @param value to be searched.
 * @return RBT node containing the value, if it exists; otherwise, NULL.
 */
rbtNode_t *rbtRecuSearch(rbt_t *t, rbtNode_t *t_rdx, const int value);

/**
 * @brief Search iteratively for a value in the RBT.
 * @param t puntatore alla struttura rbt_t
 * @param value to be searched.
 * @return RBT node containing the value, if it exists; otherwise, NULL.
 */
rbtNode_t *rbtIterSearch(rbt_t *t, const int value);

/**
 * @brief Print RBT in order.
 * @param RBT to be printed.
 * @param RBT node to be printed.
 */
void rbtInOrder(rbt_t *rbt, rbtNode_t *x);

/**
 * @brief Check if the tree is actually a RBT.
 * @param rbt to be checked.
 * @return True if it is; otherwise, false.
 */
bool isRbt(rbt_t *rbt);

/**
 * @brief Function that checks if the tree has the BST property (i.e., x->left->value < x->value <= x->right->value, for all x).
 * @param rbt to be checked.
 * @return True if it is; otherwise, false.
 */
bool rbtHasBstProperty(rbt_t *rbt);

/**
 * @brief Utility function for checking if the tree has the BST property.
 * @param Tree to be checked.
 * @param Current RBT node.
 * @param RBT test data structure.
 */
void rbtHasBstPropertyUtil(rbt_t *, rbtNode_t *, rbtTestStructure_t *);

/**
 * @brief Function that computes the black height of the RBT.
 * @param The RBT.
 * @param Current RBT node.
 * @return Black height if all paths have the same black height; otherwise, -1.
 */
int rbtComputeBlackHeight(rbt_t *, rbtNode_t *);

/**
 * @brief Free RBT nodes.
 * @param rbt whose nodes must be freed.
 * @param tnode node to be freed.
 */
void rbtFreeNodes(rbt_t *rbt, rbtNode_t *tnode);

/**
 * @brief Free RBT.
 * @param RBT to be freed.
 */
void rbtFree(rbt_t *rbt);

/**
 * @brief Check se l'array è ordinato in modo non decrescente
 * @param ptr alla struttura dati rbtTestStruct
 * @return true se ordinato, altrimenti false
*/
bool rbtIsSorted(rbtTestStructure_t *teststr);

/**
 * @brief Check se la proprietà 1 degli RBT è rispettata: ogni nodo o è rosso o è nero
 * @param rbt ptr all'RBT
 * @param tnode ptr ad un nodo dell'RBT
 * @return true se la proprietà è rispetta, false altrimenti
*/
bool rbtCheckProp_1(rbt_t *rbt, rbtNode_t *tnode);

/**
 * @brief Check se la proprietà 2 degli RBT è rispettata: la radice è nera
 * @param rbt ptr all'RBT
 * @return true se la proprietà è rispettata, false altrimenti
*/
bool rbtCheckProp_2(rbt_t *rbt);

/**
 * @brief Check se la proprietà #3 degli RBT è rispettata: tutte le foglie virtuali t.nil sono nere
 * @param rbt puntatore all'RBT
 * @param tnode node dell'RBT
 * @return true se la proprità è rispettata, false altrimenti
*/
bool rbtCheckProp_3(rbt_t *rbt, rbtNode_t *tnode);

/**
 * @brief Check se la proprietà #4 degli RBT è rispettata: se un nodo è rosso entrambi i suoi figli sono neri.
 * @param rbt ptr all'RBT
 * @return true se la proprietà è verificata, false altrimenti
*/
bool rbtCheckProp_4(rbt_t *rbt, rbtNode_t *tnode);

/**
 * @brief Check se la proprietà #5 degli RBT è rispettata: per ogni cammino semplice dalla radice alle foglie, 
 *        il numero di nodi neri e lo stesso
 * @param rbt puntatore all'RBT
 * @param tnode puntatore ad una struttura rbtNode_t
 * @return true se la proprietà è verificata, false altrimenti
*/
bool rbtCheckProp_5(rbt_t *rbt, rbtNode_t *tnode);

/**
 * @brief Test RBT if it is correctly implemented.
 * @return True if it is correct; otherwise, false.
 */
bool rbtTest();

/**
 * @brief Test the HASHTABLE if is correctly implemented
 * @return true if it is corret, false otherwise. 
 */
bool hashtableTest();

//===================================================================//
