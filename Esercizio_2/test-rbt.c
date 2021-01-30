#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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

/*=================================================*/
// FUNZIONI

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


int main(int argc, char** argv) {
    return 0;
}
