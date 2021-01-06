#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* ======================= RBT ======================= */
//
/* ====== STRUTTURE DATI ====== */

/**
 * @brief RBT node data type.
 */
typedef struct rbtNode_t
{
        // Value contained in the node.
        int value;
        // Color of the node (B or R).
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

/* ====== FINE STRUTTURE DATI ======*/

/* ===================== FUNZIONI ===================== */

/**
 * @brief Create new RBT node.
 * @param Value that the RBT node should contain.
 * @return Created RBT node.
 */
rbtNode_t *createRbtNode(const int v)
{
        /** Allocazione memoria necessaria per il nuovo nodo */
        rbtNode_t *new_node = (rbtNode_t *)malloc(sizeof(rbtNode_t));
        /** Il nodo da inserire è sempre di colore nero */
        new_node->color = 'R';
        /** Inizializzazione del puntatore al padre...*/
        new_node->parent = NULL;
        /** ... ed a figli sinistro e detro */
        new_node->left = NULL;
        new_node->right = NULL;
        /** Assegnazione del dato satellite alla chiave */
        new_node->value = v;
        /** Ritorno il nodo appena creato */
        return new_node;
}

/**
 * @brief Create new RBT.
 * @return Created RBT.
 */
rbt_t *createRbt() {
        /** Allocazione memoria necessaria la struttura di tipo rbt_t */
        rbt_t *new_rbt = (rbt_t*)malloc(sizeof(rbt_t));
        /** Puntatore t.nil, necessario per costruzione dell'rbt */
        new_rbt->nil = NULL;
        /** Inizializzazione del puntatore alla radice dell'albero */
        new_rbt->root = NULL;
        /** Dimensione iniziale dell'albero */
        new_rbt->size = 0;
        /** Ritorno il nuovo albero appena creato */
        return new_rbt;
}

/**
 * @brief Compute a left rotation of a rbt/bst
 * @param t pointer value of rbt/bst structure
 * @param x node where compute the rotation 
*/
void leftRotate(rbt_t* t, rbtNode_t* x) {
        rbtNode_t *y = x->right;
        x->right = y->left;
        if (y->left != t->nil) {
                y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == t->nil) {
                t->root = y;
        }
        if ((x->parent != t->nil) && (x == x->parent->left)) {
                x->parent->left = y;
        }
        if ((x->parent != t->nil) && (x == x->parent->right)) {
                x->parent->right = y;
        }
        y->left = y;
        x->parent = y;
}

/**
 * @brief Compute a right rotation of rbt/bst
 * @param t pointer value of rbt/bst structure
 * @param x node where compute the rotation 
*/
void rightRotate(rbt_t *t, rbtNode_t *x);

/**
 * @brief Left rotate operation.
 * @param The RBT.
 * @param The RBT node to rotate on.
 */
void rbtLeftRotate(rbt_t *t, rbtNode_t *z) {
        rbtNode_t *y = z->parent->parent->right;
        if (y->color == 'R') {
                z->parent->color = 'B';
                y->color = 'B';
                z->parent->parent->color = 'R';
                z = z->parent->parent;
        } else {
                if (z == z->parent->right) {
                        z = z->parent;
                        lefRotate(t, z);
                }
                z->parent->color = 'B';
                z->parent->parent->color = 'R';
                rightRotate(t, z->parent->parent);
        }
        return;
}

/**
 * @brief Right rotate operation.
 * @param The RBT.
 * @param The RBT node to rotate on.
 */
void rbtRightRotate(rbt_t *, rbtNode_t *);

/**
 * @brief Insert RBT node in th RBT.
 * @param The RBT.
 * @param The RBT node to be inserted.
 */
void rbtInsert(rbt_t *t, rbtNode_t *z) {
        rbtNode_t *y = t->nil;
        rbtNode_t *x = t->root;

        while(x != t->nil) {
                y = x;
                if (z->value < x->value) {
                        x = x->left;
                } else {
                        x = x->right;
                }
        }
        z->parent = y;
        
        if (y = t->nil) {
                t->root = z;
        }
        if ((y != t->nil) && (z->value <= y->value)) {
                y->left = z;
        }
        if ((y != t->nil) && (y->right > y->value)) {
                y->right = z;
        }

        z->left = t->nil;
        z->right = t->nil;
        z->color = 'R';
        rbtInsertFixup(t, z);
}

/**
 * @brief Fixup function for RBT insertion.
 * @param The RBT the be fixed.
 * @param The initial RBT node to be fixed.
 */
void rbtInsertFixup(rbt_t *t, rbtNode_t *z) {
        while (z->parent->color == 'R')
        {
                if (z->parent == z->parent->parent->left) {
                        rbtLeftRotate(t, z);
                } else {
                        rbtRightRotate(t, z);
                }
        }
        /** La radice viene sempre colora di nero all'uscita di rbtInsertFixup*/
        t->root->color = 'B';
}

/**
 * @brief Search for a value in the RBT.
 * @param The RBT.
 * @param Value to be searched.
 * @return RBT node containing the value, if it exists; otherwise, NULL.
 */
rbtNode_t *rbtSearch(rbt_t *, const int);

/**
 * @brief Print RBT in order.
 * @param RBT to be printed.
 * @param RBT node to be printed.
 */
void rbtInOrder(rbt_t *, rbtNode_t *);

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
bool isRbt(rbt_t *);

/**
 * @brief Function that checks if the tree has the BST property (i.e., x=>left=>value < x=>value <= x=>right=>value, for all x).
 * @param Tree to be checked.
 * @return True if it is; otherwise, false.
 */
bool rbtHasBstProperty(rbt_t *);

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
 * @param RBT whose nodes must be freed.
 * @param RBT node to be freed.
 */
void rbtFreeNodes(rbt_t *, rbtNode_t *);

/**
 * @brief Free RBT.
 * @param RBT to be freed.
 */
void rbtFree(rbt_t *);

/* ==================================================== */

/* ===================== MAIN ===================== */
int main(int argc, char const *argv[])
{

        return 0;
}
