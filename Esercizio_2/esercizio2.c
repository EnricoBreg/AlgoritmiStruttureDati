#include "esercizio2.h"

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

void linkedListInsert(linkedList_t *list, linkedListNode_t *x)
{
    /** Il successore di x nella lista è la "vecchia" testa della lista */
    x->next = list->head;
    /** Se la lista non è vuota... */
    if (list->head != NULL)
    {
        /** ... il predecessore della "vecchia" testa della lista 
                 * diventa x */
        list->head->prev = x;
    }
    /** Assegno x come nuova testa della lista */
    list->head = x;
    /** Il campo prev della testa viene settato a NULL */
    x->prev = NULL;
    /** Aumento la dimensione della lista */
    list->size += 1;
    /** Terminazione */
    return;
}

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
 * Per evitare errori di Segmentation Fault ho aggiunto un controllo per controllare
 * che il nodo dal eliminare dalla lista sia diverso da NULL
 */
void linkedListDelete(linkedList_t *list, linkedListNode_t *x)
{
    if (x == NULL)
    {
        /** Se il nodo da eliminare è NULL lo dealloco e termino*/
        free(x);
        return;
    }

    /** Assegnazione del nuovo valore al campo next del predeccessore */
    if (x->prev != NULL)
    {
        /** Caso di eliminazione di un nodo generico della lista */
        x->prev->next = x->next;
    }
    else
    {
        /** Caso di eliminazione del nodo in testa alla lista */
        list->head = x->next;
    }
    /** Assegnazione nuovo valore al campo prev del successore */
    if (x->next != NULL)
    {
        x->next->prev = x->prev;
    }
    /** Il nodo è irraggiungibile, lo posso deallocare */
    free(x);

    /** Diminuisco la dimensione della lista */
    list->size -= 1;

    /** Terminazione */
    return;
}

/**
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
    /* Infine, dealloco il puntatore alla testa della lista */
    free(list);
    /* Terminazione */
    return;
}

// ================================================================= //
// ----- HASHTABLE ----- //

hashtable_t *createHashtable(const unsigned int s)
{
    size_t i;
    /** Alloco la memoria per la tabella hash */
    hashtable_t *hashtbl = malloc(sizeof(hashtable_t));

    /** Assegno la dimensione della tabella hash */
    hashtbl->size = s;
    /** Alloco un array dinamico di dimensione s che conterrà i puntatori alle liste 
         * che conterranno le chiavi */
    hashtbl->entry = (hashtableEntry_t **)malloc(sizeof(hashtableEntry_t **) * s);

    for (i = 0; i < hashtbl->size; i++)
    {
        /** Alloco la new entry da essegnare alla posizione i-esima
                 * della lista */
        hashtableEntry_t *new_entry = (hashtableEntry_t *)malloc(sizeof(hashtableEntry_t *));
        /** Per la entry i-esima, creo una nuova lista collegata che 
                 * conterrà le chiavi */
        new_entry->list = createLinkedList();
        /* Assegno la new entry alla posizione i-esima */
        hashtbl->entry[i] = new_entry;
    }

    /** Ritorno la tabella hash creata */
    return hashtbl;
}

const unsigned int hashFunction(hashtable_t *hashtbl, const int v)
{
    return v % hashtbl->size;
}

void hashtableInsert(hashtable_t *hashtbl, const int v)
{
    /* Creo il nodo per la lista che conterrà l'intero v */
    linkedListNode_t *x = createLinkedListNode(v);
    /** Attraverso la funzione hash ricavo la posizione di v
         * nella entry i-esima della tabella hash */
    unsigned int i = hashFunction(hashtbl, v);
    /** Inserisco il nodo creato in testa alla lista i-esima 
         * della tabella hash */
    linkedListInsert(hashtbl->entry[i]->list, x);
    /* Terminazione */
    return;
}

/** 
 * La funzione ritorna il nodo cercato in caso di successo, altrimenti ritorna
 * NULL se il valore cercato non è presente nella tabella hash
 */
linkedListNode_t *hashtableSearch(hashtable_t *hashtbl, const int v)
{
    /** Creo un puntatore al nodo da cercare */
    linkedListNode_t *searched_node = NULL;
    /** La variabile i rappresenta la entry i-esima della tabella hash
         * dove cercare la chiave v passata */
    unsigned int i = hashFunction(hashtbl, v);
    /** Ricerca dalla chiave v nella i-esima lista della tabella hash */
    searched_node = linkedListSearch(hashtbl->entry[i]->list, v);
    /** Ritorno il nodo cercato, se la funzione di ricerca non ha ritornato nulla
         * il nodo vale NULL come valore inizialmente assegnato */
    return searched_node;
}

void hashtableDelete(hashtable_t *hashtbl, linkedListNode_t *x)
{
    unsigned int i;

    /** Questa scelta è stata fatta in quanto la operazione di eliminazione
         * viene verosimilmente collegata ad una operazione di ricerca.
         * Se il nodo cercato non esiste, allora non ha senso eliminarlo.
         * Se non fosse stata fatta tale scelta con molta probabilità si incorre
         * in un Segmentation Fault. */
    if (x == NULL)
    {
        /** Il valore del linkedListNode_t x è NULL, cioè non esiste e
                 * non ha senso proseguire */
        return;
    }

    /** Il nodo da eliminare è diverso da NULL e posso proseguire
         * con la cancellazione */
    i = hashFunction(hashtbl, x->value);

    /** Eseguo la cancellazione sulla entry i-esima della tabella hash */
    linkedListDelete(hashtbl->entry[i]->list, x);

    /** Terminazione*/
    return;
}

void hashtablePrint(hashtable_t *hashtbl)
{
    for (int i = 0; i < hashtbl->size; i++)
    {
        fprintf(stdout, "%d => ", i);
        linkedListPrint(hashtbl->entry[i]->list);
        fprintf(stdout, "\n");
    }
}

bool isHashTable(hashtable_t *hashtbl)
{
    unsigned int i;
    int hashfvalue;
    hashtable_t *tmptbl = hashtbl;
    linkedListNode_t *htelist = NULL;

    for (i = 0; i < tmptbl->size; i++)
    {
        htelist = tmptbl->entry[i]->list->head;
        while (htelist != NULL)
        {
            hashfvalue = hashFunction(tmptbl, htelist->value);
            if (hashfvalue != i)
            {
                return false;
            }
            /** Scorri la lista */
            htelist = htelist->next;
        }
        htelist = NULL;
    }

    return true;
}

void hashtableFree(hashtable_t *hashtbl)
{
    unsigned int i;

    /** Per ogni entri uso linkedListFree per deallocare l'intera
         * lista della i-esima entry
        */
    for (i = 0; i < hashtbl->size; i++)
    {
        /** Libero la memoria allocata alla lista della i-esima entry */
        linkedListFree(hashtbl->entry[i]->list);
        /** Libero la memoria della i-esima entry */
        free(hashtbl->entry[i]);
    }
    /** Deallocazione del puntatore all'array */
    free(hashtbl->entry);
    /** Una volta terminata la deallocazione di tutte le liste 
    * posso deallocare anche l'array dinamico delle entry della tabella hash */
    free(hashtbl);

    /** Terminazione */
    return;
}

// ================================================================ //

// -------------- Red Black Tree -------------- //
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

rbt_t *createRbt(void)
{
    rbt_t *new_rbt;
    rbtNode_t *t_nil;

    /** Allocazione memoria necessaria */
    new_rbt = (rbt_t *)malloc(sizeof(rbt_t));
    /** nodo T.nil */
    t_nil = createRbtNode(0);
    /** foglia virtuale sempre di colore nero */
    t_nil->color = 'B';
    /** Inizializzazione della dimensione a 0 */
    new_rbt->size = 0;
    new_rbt->nil = t_nil;
    new_rbt->root = new_rbt->nil;

    /** return del nuovo albero creato */
    return new_rbt;
}

void rbtLeftRotate(rbt_t *t, rbtNode_t *x)
{
    rbtNode_t *y;

    /** y: figlio destro del nodo x*/
    y = x->right;
    /** figlio sx di y è il figlio sinistro di x */
    x->right = y->left;

    if (y->left != t->nil)
    {
        y->left->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == t->nil)
    {
        t->root = y;
    }
    if ((x->parent != t->nil) && (x == x->parent->left))
    {
        x->parent->left = y;
    }
    if ((x->parent != t->nil) && (x == x->parent->right))
    {
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;

    return;
}

void rbtRightRotate(rbt_t *t, rbtNode_t *x)
{
    rbtNode_t *y;

    /** y: figlio destro del nodo x*/
    y = x->left;
    /** figlio sx di y è il figlio sinistro di x */
    x->left = y->right;

    if (y->right != t->nil)
    {
        y->right->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == t->nil)
    {
        t->root = y;
    }
    if ((x->parent != t->nil) && (x == x->parent->left))
    {
        x->parent->left = y;
    }
    if ((x->parent != t->nil) && (x == x->parent->right))
    {
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

    if (y->color == 'R')
    {
        /** Se lo zio è rosso, caso 2: ricolorazione */
        z->parent->color = 'B';
        y->color = 'B';
        z->parent->parent->color = 'R';

        /** "Sposto" il problema ad un livello superiore dove ci possono essere
         *  altre violazioni
        */
        z = z->parent->parent;
    }
    else
    {
        if (z == z->parent->right)
        { // Caso z figlio destro di suo padre
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

    if (y->color == 'R')
    {
        /** Se lo zio è rosso, caso 2: ricolorazione */
        z->parent->color = 'B';
        y->color = 'B';
        z->parent->parent->color = 'R';

        /** "Sposto" il problema ad un livello superiore dove ci possono essere
         *  altre violazioni
        */
        z = z->parent->parent;
    }
    else
    {
        if (z == z->parent->left)
        { // Caso z figlio destro di suo padre
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

rbtNode_t *rbtRecuSearch(rbt_t *t, rbtNode_t *t_rdx, const int value)
{
    /** Controllo che la radice non sia nil oppure che 
     *  la chiave cercata sia la chiave della radice
    */
    if ((t_rdx == t->nil) || (t_rdx->value == value))
    {
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

rbtNode_t *rbtIterSearch(rbt_t *t, const int value)
{
    rbtNode_t *aux;

    /** Controllo la radice */
    if ((t->root == t->nil) || (t->root->value == value))
    {
        return t->root;
    }

    aux = t->root;
    /** Scorro l'albero */
    while (aux != t->nil)
    {
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

void rbtInOrder(rbt_t *rbt, rbtNode_t *x)
{
    if (x != rbt->nil)
    {
        rbtInOrder(rbt, x->left);
        printf("%d ", x->value);
        rbtInOrder(rbt, x->right);
    }
}

bool isRbt(rbt_t *rbt)
{
    bool is_bst, prop1, prop2, prop3, prop4, prop5;

    // Controllo delle proprietà generali deiìl BST
    if (!(is_bst = rbtHasBstProperty(rbt)))
        return false;

    // Controllo proprieta #1 dei BST
    if (!(prop1 = rbtCheckProp_1(rbt, rbt->root)))
        return false;

    // Controllo proprieta #2 dei BST
    if (!(prop2 = rbtCheckProp_2(rbt)))
        return false;
    
    // Controllo proprieta #3 dei BST
    if (!(prop3 = rbtCheckProp_3(rbt, rbt->root)))
        return false;
    
    // Controllo proprieta #4 dei BST
    if (!(prop4 = rbtCheckProp_4(rbt, rbt->root)))
        return false;
    
    // Controllo proprieta #5 dei BST
    if (!(prop5 = rbtCheckProp_5(rbt, rbt->root)))
        return false;

    return true;
}

bool rbtHasBstProperty(rbt_t *rbt)
{
    bool is_bst = false;
    rbtTestStructure_t *teststr = NULL;

    teststr = (rbtTestStructure_t *)malloc(sizeof(rbtTestStructure_t));
    teststr->A = (int *)malloc(sizeof(int) * rbt->size);
    teststr->index = 0;

    rbtHasBstPropertyUtil(rbt, rbt->root, teststr);

    is_bst = rbtIsSorted(teststr);

    // Libero la memoria allocata
    free(teststr->A);
    free(teststr);

    if (is_bst)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void rbtHasBstPropertyUtil(rbt_t *tree, rbtNode_t *tnode, rbtTestStructure_t *teststr)
{

    /** Visita InOrder, ma gli elementi li mette nell'array della struttura dati */
    if (tnode != tree->nil)
    {
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

int rbtComputeBlackHeight(rbt_t *rbt, rbtNode_t *tnode)
{
    int left_bh, right_bh;
    left_bh = right_bh = 0;

    if (tnode == rbt->nil) // Controllo se sono arrivato alla foglia virtuale
        return 0;

    left_bh = rbtComputeBlackHeight(rbt, tnode->left);
    right_bh = rbtComputeBlackHeight(rbt, tnode->right);
    if (left_bh == -1 || right_bh == -1)
        return left_bh;
    if (left_bh != right_bh) {
        return -1;
    }
    else
    {
        if (tnode->color == 'B') // Se il nodo è nero
            return left_bh + 1;  // Aggiungo uno al contatore perchè il nodo corrente è nero
        else
            return left_bh; // Caso in cui il nodo corrente non sia nero, non si incrementa il contatore
    }
}

void rbtFreeNodes(rbt_t *rbt, rbtNode_t *tnode)
{
    // Ispirazione alla visita PostOrder, l'albero si elimina partendo dalle foglie
    if (tnode != rbt->nil)
    {
        rbtFreeNodes(rbt, tnode->left);
        rbtFreeNodes(rbt, tnode->right);
        free(tnode);
        rbt->size -= 1;
    }
    return;
}

void rbtFree(rbt_t *rbt)
{
    rbtFreeNodes(rbt, rbt->root);
    free(rbt->nil);
    free(rbt);
    return;
}

bool rbtIsSorted(rbtTestStructure_t *teststr) {
    unsigned int i = 0;

    for(i = 0; i < teststr->index-1; i++) {
        if (teststr->A[i] > teststr->A[i+1]) 
            return false;
    }
    return true;
}

bool rbtCheckProp_1(rbt_t *rbt, rbtNode_t *tnode)
{
    //  Ispirato alla visita PreOrder
    if (tnode != rbt->nil)
    {
        if (tnode->color != 'R')
        {
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

bool rbtCheckProp_2(rbt_t *rbt)
{
    if (rbt->root->color != 'B')
    {
        return false;
    }
    return true;
}

bool rbtCheckProp_3(rbt_t *rbt, rbtNode_t *tnode)
{
    // Ispirata alla visita PostOrder
    if (tnode != rbt->nil)
    {
        // Mi richiamo a sinistra
        rbtCheckProp_3(rbt, tnode->left);
        // Mi richiamo a destra
        rbtCheckProp_3(rbt, tnode->right);
    }

    if (tnode == rbt->nil)
    {
        if (tnode->color != 'B')
            return false;
    }
    return true;
}

bool rbtCheckProp_4(rbt_t *rbt, rbtNode_t *tnode)
{
    if (tnode != rbt->nil)
    {
        if (tnode->color == 'R')
        {
            if (tnode->left->color != 'B' || tnode->right->color != 'B')
            {
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

bool rbtCheckProp_5(rbt_t *rbt, rbtNode_t *tnode)
{
    int retval;
    if ((retval = rbtComputeBlackHeight(rbt, rbt->root)) == -1)
    {
        /** rbtComputeBlackHeight restituisce -1 in caso di fallimento, 
         *  => proprietà non rispettata, ritorno false 
        */
        return false;
    }
    // Altrimenti ritorno true
    return true;
}

rbtNode_t *rbtMaximum(rbt_t *rbt, rbtNode_t *tnode) {
    if (tnode->right == rbt->nil) 
        return tnode;

    return rbtMaximum(rbt, tnode->right); // Il massimo si trova nel sotto-albero dx
}

rbtNode_t *rbtMinimum(rbt_t *rbt, rbtNode_t *tnode) {
    if (tnode->left == rbt->nil) 
        return tnode;

    return rbtMinimum(rbt, tnode->left); // Il minimo si trova nel sotto-albero sx
}