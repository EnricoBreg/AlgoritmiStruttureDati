/**
 * @brief Problem 0, Laboratory of Algorithms and Data Structures.
 * @author SCIAVICCO Guido (guido.sciavicco@unife.it)
 * @author STAN Ionel Eduard (ioneleduard.stan@unife.it)
 * @version Student
 */

// ----- INCLUDED LIBRARIES ----- //

// Standard input-output library (e.g., fprintf).
#include <stdio.h>
// Time library (e.g., time, clock()).
#include <time.h>
// Standard library (e.g., rand, srand).
#include <stdlib.h>
// Boolean library (e.g., bool).
#include <stdbool.h>    // bool

// ----- End INCLUDED LIBRARIES ----- //

// ----- AUXILIARY DATA STRUCTURES ----- //

/**
 * @brief Enumeration data type for the output.
 */
typedef enum {
    ONCONSOLE,  // On console.
    ONFILE      // On file.
} outputEnumType;

// ----- End AUXILIARY DATA STRUCTURES ----- //

// ----- GLOBAL VARIABLES ----- //

// Seed (important for reproducibility).
time_t SEED = 18;
// Minimum size of the array.
const int minSize = 1000;
// Maximum size of the array.
const int maxSize = 10000;
// Number of experiments.
const int numExperiments = 10;
// Granularity of the experiment.
const int granularity = 500;
// Maximum rand6om integer allowed when generating random numbers.
const int maxRandInt = 1000000;
// Output type.
const outputEnumType outputType = ONFILE;
// Output pointer (for printing).
FILE* outputPointer;

// ----- End GLOBAL VARIABLES ----- //

// ----- AUXILIARY FUNCTIONS ----- //

/**
 * @brief Generate a collection of random numbers into an array A of size n.
 * @param A Array of random numbers.
 * @param n Size of the array.
 */
void generateRandomArray(int* A, const int n) {
    // For each i in 0..n-1, generate a random number in the interval [1,maxRandInt].
    for (int i = 0; i < n; i++) A[i] = rand() % maxRandInt + 1;
}

/**
 * @brief Display the array A of size n.
 * @param A Array to be displayed.
 * @param n Size of the array.
 */
void displayArray(int* A, int n) {
    // For each i in 0..n-1, print A[i].
    for (int i = 0; i < n; i++) printf("%d ", A[i]);
    printf("\n");
}

// ----- End AUXILIARY FUNCTIONS ----- //

// ----- CORE FUNCTIONS ----- //

/**
 * @brief Insertion sort algorithm.
 * @param A Array of random numbers to be sorted.
 * @param low Left-end index of the array.
 * @param high Right-end index of the array.
 * @property It takes time O(n^2), where n=high-low+1 is the size of the input array.
 */
void insertionSort(int* A, int low, int high) {
    int i, j, key, temp; 
    for(j = low; j <= high; j++) {
        key = A[j];
        i = j - 1;
        while((i >= 0) && (A[i] > key)) {
            // SWAP position
            //temp = A[i+1];
            A[i+1] = A[i];
            //A[i] = temp;
            i = i - 1;
        }
        A[i+1] = key;
    }

    return;
}

// ----- End CORE FUNCTIONS ----- //

// ----- ANTAGONISTIC FUNCTIONS ----- //

/**
 * @brief Unit test: check if the input array A of size n is sorted.
 * @param A Array to be checked if sorted.
 * @param n Size of the array.
 * @return true if it is sorted; otherwise, false
 */
bool isSorted(int* A, int n) {
    // For each i in 0..n-2, if the current element is greater than the next one,
    // then it is unsorted.
    for (int i = 0; i < n-1; i++) if (A[i] > A[i+1]) return false;
    // Otherwise it is.
    return true;
}

// ----- End ANTAGONISTIC FUNCTIONS ----- //

// ----- MAIN FUNCTION ----- //

/**
 * @brief Main function.
 * @return Exit code 0.
 */
int main(int argc, char *argv[]) {
    // Initialize the random seed only once.
    srand(SEED);

    // Start time.
    clock_t startTime = 0;
    // End time.
    clock_t endTime = 0;
    // Accumulated time for InsertionSort.
    clock_t timeIS = 0;
    // Flag for InsertionSort saying either that the output
    // of the execution is correct or not.
    bool isSortedIS = true;

    // Allocate an array of maxSize*sizeof(int) cells on the heap.
    // We use this array as a container.
    int* randomArray = malloc(maxSize * sizeof(int));

    // What is the outputPointer?
    if (outputType == ONCONSOLE || outputType == ONFILE) {
        // On console.
        if (outputType == ONCONSOLE) outputPointer = stdout;
        // On file.
        else {
            // Open file.
            outputPointer = fopen("results.txt", "w");
            // Have we opened the file?
            if (outputPointer == NULL) {
                fprintf(stderr, "Error: The outputPointer has not been created\n");
                exit(1);
            }
        }
    }
    // Error
    else {
        fprintf(stderr, "Error: The outputWriter can be only ONCONSOLE or ONFILE\n");
        exit(1);
    }

    // Print the header, only if it is on console

    if (outputType == ONCONSOLE) {
        fprintf(outputPointer, "+-----------+-------------------------------+\n");
        fprintf(outputPointer, "| ######### | InsertionSort                 |\n");
        fprintf(outputPointer, "+-----------+-------------------+-----------+\n");
        fprintf(outputPointer, "| Dimension | Time              | isSorted? |\n");
        fprintf(outputPointer, "+-----------+-------------------+-----------+\n");
    }


    // Going from minSize to maxSize with step equal to granularity.
    for (int dim = minSize; dim <= maxSize; dim+=granularity) {
        // Reset the accumulated time for InsertionSort from one experiment to another.
        timeIS = 0;
        // Reset the isSorted flag for InsertionSort from one experiment to another.
        // We set this flag to true at the beginning, then if at least one time
        // the InsertionSort algorithm fails to sort the input such flag will be
        // set to false; otherwise, it remains true.
        isSortedIS = true;

        // Repeat the experiment a numExperiments times for the fixed size (dim).
        for (int exper = 0; exper < numExperiments; exper++) {
            // Fill the array with (pseudo-) random numbers. That is, initialize only the
            // prefix of size dim (<= maxSize) with random numbers.
            generateRandomArray(randomArray, dim);

            // Take the start time.
            startTime = clock();
            // Do sorting with InsertionSort. Note,
            insertionSort(randomArray, 0, dim-1);
            // Take the end time.
            endTime = clock();
            // Accumulate the time.
            timeIS += endTime - startTime;

            // If the array is not sorted, then the flag is set to false.
            if (!isSorted(randomArray, dim)) isSortedIS = false;
        }
        // Printing the (sample mean as) result. Use TAB on file
        if (outputType == ONCONSOLE) 
            fprintf(outputPointer, "| %9d | %17f | %9s |\n", dim, (double) timeIS/numExperiments, isSortedIS ? "true" : "false");
        else 
            // PRINT ONFILE
            fprintf(outputPointer, "%d\t%d\t%s\n", dim, (int) timeIS/numExperiments, isSorted ? "true" : "false");
    }

    // Print the ending part, only if it is on console
    if (outputType == ONCONSOLE) fprintf(outputPointer, "+-----------+-------------------+-----------+\n");

    // Free the allocated memory.
    free(randomArray);

    // If the output is on file, we need to close the file.
    if (outputType == ONFILE)
        fclose(outputPointer);

    // We are done.
    return 0;
}

// ----- End MAIN FUNCTION ----- //
