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
// Libreria completa per esperimento 
#include "esercizio2.h"

// ----- AUXILIARY DATA STRUCTURES ----- //

/**
 * @brief Enumeration data type for the output.
 */
typedef enum outputEnum_t {
    ONCONSOLE,  // On console.
    ONFILE      // On file.
} outputEnum_t;

// ##### GLOBAL VARIABLES ###### //

// Random seed (important for reproducibility).
time_t RANDOM_SEED = 20;
// Minimum random number allowed.
const unsigned int MIN_RANDON_NUMBER = 1;
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
    // Puntatore a struttura hashtable_t
    

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

void generateRandomArray(int *a, const int n) {
    unsigned int i;
    for(i = 0; i < n; i++) {
        a[i] = MIN_RANDOM_NUMBER + rand() + MAX_RANDOM_ARRAY;
    }
    return;
}


clock_t doExperiment(int *array, const unsigned int insertionsNum, const unsigned int searchesNum, char *structName) {

    if (strcmp(structName, "hashtable") == 0) {

    }
    
    if (strcmp(structName, "rbt") == 0) {

    }

    return;
}