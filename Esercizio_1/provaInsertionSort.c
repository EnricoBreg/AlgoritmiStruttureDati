#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DIM 8
#define SEED 18
#define MAXRAND 10000
// se definito RANDOM il programma genera un array di dimensione DIM con elementi casuali compresi tra 1 e MAXRAND
//#define RANDOM
// ibidem sopra, solo per stampa array
#define PRINTARRAY

void insertionSort(int a[], int low, int right);
void stampaArray(int a[]);
bool isSorted(int a[]);

/* MAIN FUNCTION
 * Prova implementazione C dell'algoritmo di ordinamento MergeSort
 */
int main(int argc, char *argv[]) 
{
    int i;
    
    #ifdef RANDOM
    int *a;
    a = (int*)malloc(sizeof(int) * DIM);
    // Inizializzazione dell'array con numero pseudo-casuali
    for(i = 0; i < DIM; i++) 
    {
        a[i] = 1 + rand() % MAXRAND;
    }
    #else
    int a[] = {10, 3, 15, 2, 1, 4, 9, 0};
    #endif
    
    #ifdef PRINTARRAY
    stampaArray(a);
    #endif

    insertionSort(a, 0, DIM-1);

    #ifdef PRINTARRAY
    stampaArray(a);
    #endif

    bool issorted = isSorted(a);
    fprintf(stdout, "\nisSorted?\n%s\n", issorted ? "Yes" : "No");

    #ifdef RANDOM
    // deallocazione della memoria riservata all'array A
    free(a);
    #endif

    return 0;
}

void insertionSort(int* A, int low, int high) {
    int i, j, key, temp; 
    for(j = low; j <= high; j++) {
        key = A[j];
        i = j - 1;
        while((i >= 0) && (A[i] > key)) {
            // SWAP position
            temp = A[i+1];
            A[i+1] = A[i];
            A[i] = temp;
            i = i - 1;
        }
        A[i+1] = key;
    }

    return;
}

bool isSorted(int a[]) {
    int i;

    for(i = 0; i < DIM-1; i++)
    {
        if(a[i] > a[i+1])
        {
            return false;
        }
        else
        {
            return true;
        }
    }
}

void stampaArray(int a[]) 
{
    int i;
    for(i = 0; i < DIM; i++) {
        printf("%d | ", a[i]);
    }
    printf("\n");
    return;
}