//#define USE_MATH_H
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#ifdef USE_MATH_H
    #include <math.h>
#endif

static unsigned int N_KEYS = 6;
static unsigned int NIL_KEY_VALUE = -1;

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
bool isRbt(rbt_t *);

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

//===================================================================//

// MAIN 
int main(int argc, char **argv)
{

    int num = 3;
    int num_arr[] = {18, 17, 6, 20, 51, 40};
    //int num_arr[] =  {3,2,1};
    unsigned int i;
    rbt_t *t;
    rbtNode_t *nodo, *searched_node;

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
    printf("\n");

    // Prova ricerva ricorsiva di una chiave
    printf("\nProva ricerca RICORSIVA sull'albero...\n");
    searched_node = rbtRecuSearch(t, t->root, num);
    if (searched_node == t->nil) {
        printf("La chiave cercata non esiste nell'RBT\n");
    } else {
        printf("La chiave cercata esiste\n");
    }

    // Prova ricerva iterativa
    printf("\nProva ricerca ITERATIVA sull'albero...\n");
    searched_node = rbtIterSearch(t, num);
    if (searched_node == t->nil) {
        printf("La chiave cercata non esiste nell'RBT\n");
    } else {
        printf("La chiave cercata esiste\n");
    }

    // Controllo
    isRbt(t);

    printf("\n");
    printf("Altezza nera dell'albero: %d", rbtComputeBlackHeight(t, t->root));
    printf("\n");

    // prova eliminazione di un nodo
    printf("\nEliminazione dell'albero...\n");
    rbtFreeNodes(t, t->root);
    rbtFree(t);

    printf("\nBYE!\n\n");
    return 0;
}
// FINE MAIN


// =================================================================== //
// DEFINIZIONE FUNZIONI

rbtNode_t *createRbtNode(const int key)
{
    rbtNode_t *new_rbt_node;

    /** Allocazione della memoria necessaria per new_rbt_node */
    new_rbt_node = (rbtNode_t *)malloc(sizeof(rbtNode_t));
    /** Inizializzazione dei campi della struttura */
    memset(new_rbt_node, 0, sizeof(rbtNode_t));
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
    t_nil = createRbtNode(NIL_KEY_VALUE);
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
        rbtNode_t *y;

    /** y: figlio destro del nodo x*/
    y = x->left;
    /** figlio sx di y è il figlio sinistro di x */
    x->left = y->right;

    if (y->right != t->nil) {
        y->right->parent = x;
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

    y->right = x;
    x->parent = y;

    return;
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
            rbtInsertFixupLeft(t, z);
        else
            rbtInsertFixupRight(t, z);
    }
    /** Sistemo l'eventuale violazione della proprietà 2 */
    t->root->color = 'B';

    return;
}

rbtNode_t *rbtRecuSearch(rbt_t *t, rbtNode_t *t_rdx, const int value) {
    /** Controllo che la radice non sia nil oppure che 
     *  la chiave cercata sia la chiave della radice
    */
    if ((t_rdx == t->nil) || (t_rdx->value == value)) {
        return t_rdx;
    }
    /** Scorro l'albero in cerca della chiave */
    if (value < t_rdx->value)
        /** La chiave è nel sotto-albero sx*/
        return rbtRecuSearch(t, t_rdx->left, value);
    else 
        /** La chiave è nel sotto-albero dx */
        return rbtRecuSearch(t, t_rdx->right, value);
}

rbtNode_t *rbtIterSearch(rbt_t *t, const int value) {
    rbtNode_t *aux;

    /** Controllo la radice */
    if ((t->root == t->nil) || (t->root->value == value)) {
        return t->root;
    }

    aux = t->root;
    /** Scorro l'albero */
    while (aux != t->nil) {
        if (value < aux->value)
            /** Vado a sinistra */
            aux = aux->left;
        else
            aux = aux->right;
        
        if (aux->value == value) 
            return aux;   
    }
    
    return aux;
}

void rbtInOrder(rbt_t *rbt, rbtNode_t *x) {
    if (x != rbt->nil) {
        rbtInOrder(rbt, x->left);
        printf("%d ", x->value);
        rbtInOrder(rbt, x->right);
    }
}

bool isRbt(rbt_t *rbt) {
    bool is_bst, prop1, prop2, prop3, prop4, prop5;

    // Controllo delle proprietà generali deiìl BST
    if (!(is_bst = rbtHasBstProperty(rbt))) {
        fprintf(stderr, "\nERRORE. Proprietà BST non rispettate!\n");
        exit(EXIT_FAILURE);
    }
    
    // Controllo proprieta #1 dei BST
    if (!(prop1 = rbtCheckProp_1(rbt, rbt->root))) {
        fprintf(stderr, "\nERRORE. Proprietà RBT #1 non rispettata!\n");
        exit(EXIT_FAILURE);
    }
    // Controllo proprieta #2 dei BST
    if (!(prop2 = rbtCheckProp_2(rbt))) {
        fprintf(stderr, "\nERRORE. Proprietà RBT #2 non rispettata!\n");
        exit(EXIT_FAILURE);
    }
    // Controllo proprieta #3 dei BST
    if (!(prop3 = rbtCheckProp_3(rbt, rbt->root))) {
        fprintf(stderr, "ERRORE. Proprietà RBT #3 non rispettata!\n");
        exit(EXIT_FAILURE);
    }
    // Controllo proprieta #4 dei BST
    if (!(prop4 = rbtCheckProp_4(rbt, rbt->root))) {
        fprintf(stderr, "ERRORE. Proprietà RBT #4 non rispettata!\n");
        exit(EXIT_FAILURE);
    }
    // Controllo proprieta #5 dei BST
    if (!(prop5 = rbtCheckProp_5(rbt, rbt->root))) {
        fprintf(stderr, "ERRORE. Proprietà RBT #5 non rispettata!\n");
        exit(EXIT_FAILURE);
    }
    
    return true;
}

bool rbtHasBstProperty(rbt_t *rbt) {
    bool is_bst = false;
    rbtTestStructure_t *teststr = NULL;

    teststr = (rbtTestStructure_t*)malloc(sizeof(rbtTestStructure_t));
    teststr->A = (int*)malloc(sizeof(int)*rbt->size);
    teststr->index = 0;

    rbtHasBstPropertyUtil(rbt, rbt->root, teststr);

    is_bst = rbtIsSorted(teststr);

    // Libero la memoria allocata
    free(teststr->A);
    free(teststr);

    if (is_bst) {
        return true;
    }
    else {
        return false;
    }
}

void rbtHasBstPropertyUtil(rbt_t *tree, rbtNode_t *tnode, rbtTestStructure_t *teststr) {

    /** Visita InOrder, ma gli elementi li mette nell'array della struttura dati */
    if (tnode != tree->nil) {
        /** Mi richiamo sul sotto-albero sinistro */
        rbtHasBstPropertyUtil(tree, tnode->left, teststr);
        /** Copio l'elemento nell'indice */
        teststr->A[teststr->index] = tnode->value;
        /** Incremento l'indice dell'array */
        teststr->index += 1;
        /** Mi richiamo a destra */
        rbtHasBstPropertyUtil(tree, tnode->right, teststr);
    }

    return;
}

int rbtComputeBlackHeight(rbt_t *rbt, rbtNode_t *tnode) {
    int left_bh, right_bh;
    left_bh = right_bh = 0;

    if (tnode == rbt->nil) // Controllo se sono arrivato alla foglia virtuale
        return 0;

    left_bh = rbtComputeBlackHeight(rbt, tnode->left);
    right_bh = rbtComputeBlackHeight(rbt, tnode->right);
    if (left_bh == -1) 
        return left_bh;
    if (right_bh == -1) 
        return right_bh;

    if (left_bh != right_bh) {
        return -1;
    } else {
        if (tnode->color == 'B') // Se il nodo è nero 
            return left_bh + 1;  // Aggiungo uno al contatore perchè il nodo corrente è nero
        else   
            return left_bh;      // Caso in cui il nodo corrente non sia nero, non si incrementa il contatore
    }

}

void rbtFreeNodes(rbt_t *rbt, rbtNode_t *tnode) {
    // Ispirazione alla visita PostOrder, l'albero si elimina partendo dalle foglie
    if (tnode != rbt->nil) {
        rbtFreeNodes(rbt, tnode->left);
        rbtFreeNodes(rbt, tnode->right);
        free(tnode);
        rbt->size -= 1;
    }
    return;
}

void rbtFree(rbt_t *rbt) {
    free(rbt->nil);
    free(rbt);
    return;
}

bool rbtIsSorted(rbtTestStructure_t *teststr) {
    unsigned int i = 0;

    for(i = 0; i < teststr->index-1; i++) {
        if (teststr->A[i] < teststr->A[i++]) 
            return false;
    }
    return true;
}

bool rbtCheckProp_1(rbt_t *rbt, rbtNode_t *tnode) {
    //  Ispirato alla visita PreOrder
    if (tnode != rbt->nil) {
        if (tnode->color != 'R') {
            if (tnode->color != 'B')
                return false;
        }
        // Mi richiamo a sinistra
        rbtCheckProp_1(rbt, tnode->left);
        // Mi richiamo a destra
        rbtCheckProp_1(rbt, tnode->right);
    }

    return true;
}

bool rbtCheckProp_2(rbt_t *rbt) {
    if (rbt->root->color != 'B') {
        return false;
    }
    return true;
}

bool rbtCheckProp_3(rbt_t *rbt, rbtNode_t *tnode) {
    // Ispirata alla visita PostOrder
    if (tnode != rbt->nil) {
        // Mi richiamo a sinistra
        rbtCheckProp_3(rbt, tnode->left);
        // Mi richiamo a destra
        rbtCheckProp_3(rbt, tnode->right);
    }
    
    if (tnode == rbt->nil) {
        if(tnode->color != 'B')
            return false;
    }
    return true;
}

bool rbtCheckProp_4(rbt_t *rbt, rbtNode_t *tnode) {
    if (tnode != rbt->nil) {
        if (tnode->color == 'R') {
            if (tnode->left->color != 'B' || tnode->right->color != 'B') {
                return false;
            }
        }
        // Mi richiamo sul sotto-albero sx
        rbtCheckProp_4(rbt, tnode->left);
        // Mi richiamo sul sotto-albero dx
        rbtCheckProp_4(rbt, tnode->right);
    }
    return true;
}

bool rbtCheckProp_5(rbt_t *rbt, rbtNode_t *tnode) {
    int retval;
    if ((retval = rbtComputeBlackHeight(rbt, rbt->root)) == -1) {
        /** rbtComputeBlackHeight restituisce -1 in caso di fallimento, 
         *  => proprietà non rispettata, ritorno false 
        */
        return false;
    }
    // Altrimenti ritorno true
    return true;
}