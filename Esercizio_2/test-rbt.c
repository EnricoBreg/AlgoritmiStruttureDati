#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

static unsigned int N_KEYS = 3;

// DICHIARAZIONE TIPI DI DATO E PROTOTIPI FUNZIONI

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
rbt_t *createRbt();

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
 * @brief Function that checks if the tree has the BST property (i.e., x->left->value < x->value <= x->right->value, for all x).
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


//===================================================================//

// MAIN 
int main(int argc, char **argv)
{

    // int num = 18;
    // int num_arr[] = {18, 17, 6, 20, 51, 40};
    int num_arr[] =  {1, 2, 3};
    unsigned int i;
    rbt_t *t;
    rbtNode_t *nodo;

    //printf("\nInserimento %d nell'albero...\n");
    t = createRbt();

    printf("\nInserimento di nuovi nodi...\n");
    for (i = 0; i < N_KEYS; i++) {
        // crea il nodo
        printf("Alloco memoria per il nodo con chiave %d...\n", num_arr[i]);
        nodo = createRbtNode(num_arr[i]);
        // Inseriscilo
        printf("Inserisco il nuovo nodo con chiave %d e colore %c nell'albero...\n\n", nodo->value, nodo->color);
        rbtInsert(t, nodo);
    }   
    printf("\n");
    printf("t->size: %d\n", t->size);

    // visita dell'albero
    printf("\nVisito l'albero...\n");
    rbtInOrder(t, t->root);

    printf("\n\n\nh albero: log2(%d) = %d\n", t->size, (int)log2f((float)t->size));

    printf("\n");


    return 0;
}
// FINE MAIN


//===================================================================//
// DEFINIZIONE FUNZIONI

rbtNode_t *createRbtNode(const int key)
{
    rbtNode_t *new_rbt_node;

    /** Allocazione della memoria necessaria per new_rbt_node */
    new_rbt_node = (rbtNode_t *)malloc(sizeof(rbtNode_t));
    /** Inizializzazione dei campi della struttura */
    memset(new_rbt_node, 0, sizeof(new_rbt_node));
    /** Ogni nuovo nodo inserito nell'albero ha colore RED */
    new_rbt_node->color = 'R';
    /** Assegnazione della chiave al nodo */
    new_rbt_node->value = key;

    /** return del nuovo nodo allocato */
    return new_rbt_node;
}


rbt_t *createRbt()
{
    rbt_t *new_rbt;
    rbtNode_t *t_nil;

    /** Allocazione memoria necessaria */
    new_rbt = (rbt_t *)malloc(sizeof(rbt_t));
    /** nodo T.nil */
    t_nil = (rbtNode_t *)malloc(sizeof(rbtNode_t));
    memset(t_nil, 0, sizeof(t_nil));
    /** foglia virtuale sempre di colore nero */
    t_nil->color = 'B';
    /** Inizializzazione della dimensione a 0 */
    new_rbt->size = 0;
    new_rbt->nil = t_nil;
    new_rbt->root = new_rbt->nil;

    /** return del nuovo albero creato */
    return new_rbt;
}


void rbtLeftRotate(rbt_t *t, rbtNode_t *x) {
    rbtNode_t *y;

    /** y: figlio destro del nodo x*/
    y = x->right;
    /** figlio sx di y è il figlio sinistro di x */
    x->right = y->left;

    if (y->left != t->nil) {
        y->left->parent = x;
    }
    
    y->parent = x->parent;

    if (x->parent == t->nil) {
        t->root = y;
    }
    if ((x->parent != t->nil) &&  (x == x->parent->left)) {
        x->parent->left = y;
    }
    if ((x->parent != t->nil) && (x == x->parent->right)) {
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;

    return;
}

void rbtRightRotate(rbt_t *t, rbtNode_t *x) {

}


void rbtInsert(rbt_t *t, rbtNode_t *z)
{

    /** ptr x: scorre la struttura */
    /** ptr y: padre del nuovo nodo z */
    rbtNode_t *y = t->nil;
    rbtNode_t *x = t->root;

    /** Trovo la posizione corretta del padre di z nell'albero */
    while (x != t->nil) // Proseguo finchè non arrivo ad una foglia virtualee
    {
        y = x;
        /** Scelgo se andare nel sotto-albero sx o dx */
        if (z->value < x->value)
        {
            /** Sotto-albero sx */
            x = x->left;
        }
        else
        {
            /** Sotto-albero dx */
            x = x->right;
        }
    }
    /** All'uscita dal ciclo y sarà il corretto padre di z */
    z->parent = y;

    if (y == t->nil)
    {
        /** Inserisco il nuovo nodo come radice dell'albero */
        t->root = z;
    }
    if ((y != t->nil) && (z->value < y->value))
    {
        /** Inserisci il nodo nel sotto-albero sx di y */
        y->left = z;
    }
    if ((y != t->nil) && (z->value >= y->value))
    {
        /** Inserisci il nodo nel sotto-albero dx di y */
        y->right = z;
    }

    /** I figli del nuovo nodo sono foglie virtuali */
    z->left = z->right = t->nil;
    /** Il colore è stato assegnato durante l'allocazione del nodo */

    /** Aumento la dimensione dell'albero */
    t->size += 1;

    /** Chiamo la procedura di fixup dell'albero */
    rbtInsertFixup(t, z);

    return;
}

void rbtInsertFixupLeft(rbt_t *t, rbtNode_t *z)
{
    /** y = Zio di z */
    rbtNode_t *y = z->parent->parent->right;

    if (y->color == 'R') {
        /** Se lo zio è rosso, caso 2: ricolorazione */
        z->parent->color = 'B';
        y->color = 'B';
        z->parent->parent->color = 'R';

        /** "Sposto" il problema ad un livello superiore dove ci possono essere
         *  altre violazioni
        */
        z = z->parent->parent; 
    } else {
        if (z == z->parent->right) { // Caso z figlio destro di suo padre
            z = z->parent;
            rbtLeftRotate(t, z);
        }

        /** Ricolorazione */
        z->parent->color = 'B';
        z->parent->parent->color = 'R';
        /** Rotazione per bilanciare l'albero */
        rbtRightRotate(t, z->parent->parent);
    }

    return; 
}


void rbtInsertFixupRight(rbt_t *t, rbtNode_t *z)
{
    /** y = Zio di z */
    rbtNode_t *y = z->parent->parent->left;

    if (y->color == 'R') {
        /** Se lo zio è rosso, caso 2: ricolorazione */
        z->parent->color = 'B';
        y->color = 'B';
        z->parent->parent->color = 'R';

        /** "Sposto" il problema ad un livello superiore dove ci possono essere
         *  altre violazioni
        */
        z = z->parent->parent; 
    } else {
        if (z == z->parent->left) { // Caso z figlio destro di suo padre
            z = z->parent;
            rbtRightRotate(t, z);
        }

        /** Ricolorazione */
        z->parent->color = 'B';
        z->parent->parent->color = 'R';
        /** Rotazione per bilanciare l'albero */
        rbtLeftRotate(t, z->parent->parent);
    }

    return; 
}


void rbtInsertFixup(rbt_t *t, rbtNode_t *z)
{
    /** Finchè padre e figlio hanno colore rosso */
    while (z->parent->color == 'R')
    {
        /** Se il padre di z e figlio sx di suo padre */
        if (z->parent->parent->left == z->parent)
        {
            rbtInsertFixupLeft(t, z);
        }
        else
        {
            rbtInsertFixupRight(t, z);
        }
    }
    /** Sistemo l'eventuale violazione della proprietà 2 */
    t->root->color = 'B';

    return;
}


rbtNode_t *rbtSearch(rbt_t *, const int);

void rbtInOrder(rbt_t *rbt, rbtNode_t *x) {
    if (x != rbt->nil) {
        rbtInOrder(rbt, x->left);
        printf("%d ", x->value);
        rbtInOrder(rbt, x->right);
    }
}

bool rbtTest();

bool isRbt(rbt_t *);

bool rbtHasBstProperty(rbt_t *);

void rbtHasBstPropertyUtil(rbt_t *, rbtNode_t *, rbtTestStructure_t *);

int rbtComputeBlackHeight(rbt_t *, rbtNode_t *);

void rbtFreeNodes(rbt_t *, rbtNode_t *);

void rbtFree(rbt_t *);
