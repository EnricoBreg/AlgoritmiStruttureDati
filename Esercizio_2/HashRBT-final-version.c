/**
 * @brief Problem 2, Laboratory of Algorithms and Data Structures.
 * @author SCIAVICCO Guido (guido.sciavicco@unife.it)
 * @author STAN Ionel Eduard (ioneleduard.stan@unife.it)
 * @version Student
 */

// Comment this line if want use Iterative line, uncomment otherwise for Recursive Search
// #define USE_RBT_RECURSIVE_SEARCH

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
// Libreria completa per esperimento
#include "esercizio2.h"

// ----- AUXILIARY DATA STRUCTURES ----- //

/**
 * @brief Enumeration data type for the output.
 */
typedef enum outputEnum_t
{
    ONCONSOLE, // On console.
    ONFILE     // On file.
} outputEnum_t;

// ##### GLOBAL VARIABLES ###### //

// Random seed (important for reproducibility).
time_t RANDOM_SEED = 18;
// Maximum random number allowed.
const unsigned int MAX_RANDOM_NUMBER = 10000000;
// Minimum number of operations.
const unsigned int MIN_OPERATIONS = 100; 
// Maximum number of operations.
const unsigned int MAX_OPERATIONS = 4000; 
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
const outputEnum_t outputType = ONCONSOLE;
// Output pointer (for printing).
FILE *outputPointer;

// ----- AUXILIARY FUNCTIONS ----- //
/**
 * @brief Generate a collection of random numbers.
 * @param Array of random numbers.
 * @param Size of the array.
 */
void generateRandomArray(int *, const int);

/**
 * @brief Generate a random number between 0 and MAX_RANDOM_NUMBER
 * @param MAX_RAND_NUM the max random number to generate
 * @return int random number generated
 */
int generateRandomNumber(int MAX_RAND_NUM);

// ----- End of AUXILIARY FUNCTIONS ----- //

// ----- CORE FUNCTIONS ----- //

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

/**
 * @brief Function that does the experiment.
 * @param Array of random numbers.
 * @param Number of insertion operations.
 * @param Number of search operations.
 * @param Data structure to be used. The possible values are:
 * @return Elapsed time for the experiment.
 */
clock_t doExperiment(int *, const unsigned int, const unsigned int, char *);

// ----- End of CORE FUNCTIONS ----- //

// ##### End of PROTOTYPES OF THE FUNCTIONS ##### //

int main(int argc, char *argv[])
{

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
    if (outputType == ONCONSOLE || outputType == ONFILE)
    {
        // On console.
        if (outputType == ONCONSOLE)
            outputPointer = stdout;
        // On file.
        else
        {
            // Open file.
            outputPointer = fopen("results.txt", "w");
            // Have we opened the file?
            if (outputPointer == NULL)
            {
                fprintf(stderr, "ERROR: The outputPointer has not been created\n");
                exit(-1);
            }
        }
    }
    // Error
    else
    {
        fprintf(stderr, "ERROR: The outputType can be only ONCONSOLE or ONFILE\n");
        exit(-1);
    }

    // Print the header, only if it is on console.
    if (outputType == ONCONSOLE)
    {
        fprintf(outputPointer, "+-----------------------------+---------------------+---------------------+\n");
        fprintf(outputPointer, "| Operations - %%I & %%S        | Hashtable - %-5d   | Red Black Tree      |\n", NUM_ENTRIES);
        fprintf(outputPointer, "+-----------------------------+---------------------+---------------------+\n");
    }

    // For each number of operations in the interval [MIN_OPERATIONS, MAX_OPERATIONS] with STEP
    for (int numOps = MIN_OPERATIONS; numOps <= MAX_OPERATIONS; numOps += STEP)
    {
        // Reset the times.
        timeHashtable = timeRbt = 0;
        // For each experiment
        for (int exper = 1; exper <= NUM_EXPERIMENTS; exper++)
        {

            // Compute the number of insert operations.
            numInsertions = numOps * PERCENTAGE_INSERTIONS / 100;
            // Compute the number of search operations.
            numSearches = numOps - numInsertions;
            // Allocate numInsertions memory cells for the array of random numbers.
            int *randomArray = (int*)malloc(numInsertions * sizeof(int));
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
                    100 - PERCENTAGE_INSERTIONS,
                    (float)timeHashtable / NUM_EXPERIMENTS,
                    (float)timeRbt / NUM_EXPERIMENTS);
        else
            fprintf(outputPointer, "%d \t%f \t%f \n",
                    numOps,
                    (float)timeHashtable / NUM_EXPERIMENTS,
                    (float)timeRbt / NUM_EXPERIMENTS);
    }

    // Print the ending part, only if it is on console.
    if (outputType == ONCONSOLE)
    {
        fprintf(outputPointer, "+-----------------------------+---------------------+---------------------+\n");
        fprintf(outputPointer, "| Legend:                                                                 |\n");
        fprintf(outputPointer, "|                                                                         |\n");
        fprintf(outputPointer, "| %%I: Percentage of insertion operations                                  |\n");
        fprintf(outputPointer, "| %%S: Percentage of search operations                                     |\n");
        fprintf(outputPointer, "|                                                                         |\n");
        fprintf(outputPointer, "| The number near \"Hashtable\" is the number of entries in the hashtable   |\n");
        fprintf(outputPointer, "+-------------------------------------------------------------------------+\n");
    }

    if (TEST_DATA_STRUCTURES && outputType == ONCONSOLE)
    {
        fprintf(outputPointer, "| Hashtable implementation: %-12s                                  |\n", hashtableTest() ? "correct" : "not correct");
        fprintf(outputPointer, "| Red black tree implementation: %-12s                             |\n", rbtTest() ? "correct" : "not correct");
        fprintf(outputPointer, "+-------------------------------------------------------------------------+\n");
    }
    // Chiudo il file results.txt
    if (outputType == ONFILE) {
        fclose(outputPointer);
    }

    // Return 0.
    return 0;
}

void generateRandomArray(int *a, const int n) {
    unsigned int i;
    for (i = 0; i < n; i++) {
        a[i] = 1 + rand() % MAX_RANDOM_NUMBER;
    }

    return;
}

// Generazione di un numero casuale
int generateRandomNumber(int MAX_RAND_NUM) {
    return rand() % MAX_RAND_NUM; 
}

bool rbtTest() { // Opearazioni da testare: creazione, inserimento, ricerca, massimo, minimo
    unsigned int i;                                            
    int *a;                                                         // Array con le chiavi da inserire nell'albero da testare
    rbt_t *rbt = NULL;                                              // Puntatore all'albero RBT da testare
    rbtNode_t *search_node = NULL, *node = NULL;                    // Nodo per la ricerca della chiave

    a = (int*)malloc(sizeof(int)*NUM_ELEMENTS_FOR_TEST);   // Allocazione della memoria per l'array di chiavi generate

    // Seed per i numeri casuali, definito all'inizio
    srand(RANDOM_SEED);

    generateRandomArray(a, NUM_ELEMENTS_FOR_TEST); // Genero casualmente l'array
    
    rbt = createRbt(); // Creazione rbt
    if (rbt == NULL) {
        fprintf(stderr, "| ERRORE. Creazione rbt non andata a buon fine\n");
        return false;
    }

    for (i = 0; i < NUM_ELEMENTS_FOR_TEST; i++) {
        node = createRbtNode(a[i]); // Creo il nodo
        rbtInsert(rbt, node);       // Lo inserisco nell'albero
    }

    // Test delle proprietà rbt
    if (isRbt(rbt) == false){
        fprintf(stderr, "| ERRORE. Proprietà BST o RBT non rispettate\n");
        return false;
    }

    // Tesst ricerca iterativa di un nodo esistente
    search_node = rbtIterSearch(rbt, a[generateRandomNumber(NUM_ELEMENTS_FOR_TEST)]);
    // Test del valore ritornato dalla ricerca
    if (search_node == rbt->nil) {
        // Se è una foglia nil, allora la ricerca non è andata a buon fine
        fprintf(stderr, "| ERRORE. Ricerca non corretta\n");
        return false;
    }

    // Test ricerca ricorsiva, stesso principio di prima
    search_node = rbtRecuSearch(rbt, rbt->root, a[generateRandomNumber(NUM_ELEMENTS_FOR_TEST)]);
    if (search_node == rbt->nil) {
        fprintf(stderr, "| ERRORE. Ricerca ricorsiva non andata a buon fine\n");
        return false;
    }

    rbtNode_t *max = NULL, *min = NULL;
    max = rbtMaximum(rbt, rbt->root);   // Ricerca del massimo
    min = rbtMinimum(rbt, rbt->root);   // Ricerca del minimo
    // Controllo del valore ritornato
    if (max == rbt->nil || min == rbt->nil) {
        fprintf(stderr, "| ERRORE. Ricerca del massimo o del minimo non andate a buon fine\n");
        return false;
    }

    // Libero la memoria allocata
    rbtFree(rbt);       // Per l'albero
    free(a);            // Per l'array di numeri casuali

    // Se la procedura di test è arrivata fino a qui, allora la struttura dati è correttamente implementata
    return true;
}

bool hashtableTest() { // Operazioni da testare creazione, inserimento, ricerca
    unsigned int i, n_entries = 12;                                            
    int *a;                                             // Array con le chiavi da inserire nell'albero da testare
    hashtable_t *hashtable = NULL;                      // Puntatore alla struttura hastable
    linkedListNode_t *searched_node = NULL;             // Puntatore ad un nodo della lista collegata
    
    // Seed per i numeri casuali, definito all'inizio
    srand(RANDOM_SEED);

    if (NUM_ENTRIES <= 1) {
        fprintf(stderr, "| ERRORE. Il numero di entries di hash table deve essere maggiore di 1\n");
    }

    a = (int*)malloc(sizeof(int)*NUM_ELEMENTS_FOR_TEST); // Allocazione della memoria per le chiavi
    generateRandomArray(a, NUM_ELEMENTS_FOR_TEST);

    // Creazione della tabella hash non n_entries
    hashtable = createHashtable(n_entries);
    if (hashtable == NULL) {
        fprintf(stderr, "| ERRORE. Creazione della hash table non andata a buon finen");
        return false;
    }

    // Inserimento chiavi nella hash table
    for (i = 0; i < NUM_ELEMENTS_FOR_TEST; i++) {
        hashtableInsert(hashtable, a[i]);
    }

    // Controllo aggiuntivo sulla struttura dati
    if (isHashTable(hashtable) == false) {
        return false;
    }
    
    // Test ricerca di una chiave inserita
    searched_node = NULL;
    searched_node = hashtableSearch(hashtable, a[generateRandomNumber(NUM_ELEMENTS_FOR_TEST)]);
    if (searched_node == NULL) {
        // Allora la ricerca di una chiave ESISTENTE non è andata a buon fine
        fprintf(stderr, "| ERRORE. Ricerca della chiave non andata a buon fine\n");
        return false;
    }

    // Test eliminazione di un nodo, uso il nodo cercare che so per certo esistere
    hashtableDelete(hashtable, searched_node);
    int num = searched_node->value;
    if (hashtableSearch(hashtable, num) != NULL) {
        fprintf(stderr, "| ERRORE. Eliminazione nodo non andata a buon fine\n");
        return false;
    }

    // Libero la memoria allocata
    hashtableFree(hashtable);   // Per la tabella hash
    free(a);                    // Per l'array di numeri casuali

    // Se la procedura di test è arrivata fino a qui, allora la struttura dati è correttamente implementata
    return true;
}

clock_t doExperiment(int *a, const unsigned int num_insertions, const unsigned int num_searches, char *data_structre) {
    unsigned int i;
    int searched_key;
    clock_t start_time = 0, end_time = 0;
    // In base al valore di data_structure si esegue l'esperimento
    if (strcmp(data_structre, "hashtable") == 0) {  // Test della tabella hash
        
        hashtable_t* hashtable = NULL;      // Puntatore all struttra dati
        linkedListNode_t *llnode = NULL;    // linkedListNode usato per la ricerca
        hashtable = createHashtable(NUM_ENTRIES); // Creazione della tabella hash con numero di entries = NUM_ENTRIES

        // Inizio conteggio del tempo
        start_time = clock(); 

        // Eseguo n_insertions
        for (i = 0; i < num_insertions; i++) {
            hashtableInsert(hashtable, a[i]);
        }

        // Eseguo le ricerche
        for (i = 0; i < num_searches; i++) {
            searched_key = generateRandomNumber(MAX_RANDOM_NUMBER);
            llnode = hashtableSearch(hashtable, searched_key);
        }

        // Fine conteggio del tempo
        end_time = clock(); 

        // Libero la memoria allocata 
        hashtableFree(hashtable);   // Alla hash table
        free(llnode);               // del nodo usato per la ricerca
    }
    else if (strcmp(data_structre, "rbt") == 0) {        // Test dell'rbt
        rbt_t *rbt = NULL; // Puntatore all struttra dati
        rbtNode_t *tnode = NULL;
        rbt = createRbt(); // Creazione della struttura dati

        // Inizio conteggio del tempo
        start_time = clock(); 

        // Eseguo nun_inseritions
        for(i = 0; i < num_insertions; i++) {
            tnode = createRbtNode(a[i]);
            rbtInsert(rbt, tnode);
        }

        // Eseguo num_searches
        for (i = 0; i < num_searches; i++) {
            searched_key = generateRandomNumber(MAX_RANDOM_NUMBER);
#ifdef USE_RBT_RECURSIVE_SEARCH
            tnode = rbtRecuSearch(rbt, rbt->root, searched_key);
#else
            tnode = rbtIterSearch(rbt, searched_key);
#endif        
        }

        // Fine conteggio del tempo
        end_time = clock();

        // Libero la memoria allocata per rbt
        rbtFree(rbt);   
    }
    else {
        fprintf(stderr, "| ERRORE. Specificate una struttura dati da testare. 'hashtable' o 'rbt'\n");
        exit(EXIT_FAILURE);
    }

    // Ritorno del tempo impiegato per l'esperimentp
    return (end_time - start_time);
}