#include <stdio.h>
#include <stdlib.h>

#define DIM 12
#define SEED 18
//#define RANDOM

void merge(int*, int, int, int );
void mergeSort(int*, int, int);
void stampaArray(int A[]);


/* MAIN FUNCTION
 * Prova implementazione C dell'algoritmo di ordinamento MergeSort
 */
int main(int argc, char *argv[]) {
    int i;
    
    #ifdef RANDOM
    int *A;
    A = (int*)malloc(sizeof(int) * DIM);
    // Inizializzazione dell'array con numero pseudo-casuali
    for(i = 0; i < DIM; i++) {
        A[i] = 1 + rand() % 100;
    }
    #else
    int A[] = {34, 77, 29, 96, 28, 10, 16, 9, 69, 39, 98, 23};
    #endif
    
    stampaArray(A);
    mergeSort(A, 0, DIM-1);

    stampaArray(A);

    #ifdef RANDOM
    // deallocazione della memoria riservata all'array A
    free(A);
    #endif

    return 0;
}

void merge(int *A, int p, int q, int r) {
    int n1 = q - p;
    int n2 = r - q;
    int i, j, k;
    // Array di appoggio
    int *L, *R;
    L = (int*)malloc(n1 * sizeof(int));
    R = (int*)malloc(n2 * sizeof(int));

    /* 
     * Gli elementi dall'indice (p+i-1) a n1 vengono copiati nell'array di appoggio L
     * Gli elementi dall'indice q a n2 vengono copiati nell'array di appoggio R
     */
    for(i = 0; i < n1; i++) {    
        L[i] = A[p + i];   
    }

    for(j = 0; j < n2; j++) {
        R[j] = A[q + j];
    }

    i = j = 0;

    for(k = p; k < r; k++) {
        if(i < n1) {
            if(L[i] <= R[j] || j == n2 + 1) {
                // Copia da L ed incrementa i
                A[k] = L[i];
                i++;
            }
            else 
            {
                // Copia da R ed incrementa j
                A[k] = R[j];
                j++;
            }
        }
        else {
            // Copia da R ed incrementa j
            A[k] = R[j];
            j++;
        }
    }

    free(L);
    free(R);

    return;
}

void mergeSort(int* A, int p, int r) {
    int q;

    if(p < r) {
        q = (p+r) / 2;
        mergeSort(A, p, q);
        mergeSort(A, q+1, r);
        merge(A, p, q, r);
    }
    
    return;
}


void stampaArray(int A[]) {
    int i;
    for(i = 0; i < DIM; i++) {
        printf("%d | ", A[i]);
    }
    printf("\n");
    return;
}