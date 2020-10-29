#include <stdio.h>
#include <stdlib.h>

#define DIM 8
#define SEED 18
#define MAXRAND 100
// se definito RANDOM il programma genera un array di dimensione DIM con elementi casuali compresi tra 1 e MAXRAND
#define RANDOM

void merge(int *a, int left, int center, int right);
void mergeSort(int *a, int left, int right);
void stampaArray(int a[]);


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
    for(i = 0; i < DIM; i++) {
        a[i] = 1 + rand() % MAXRAND;
    }
    #else
    int a[] = {10, 3, 15, 2, 1, 4, 9, 0};
    #endif
    
    stampaArray(a);

    mergeSort(a, 0, DIM-1);

    stampaArray(a);

    #ifdef RANDOM
    // deallocazione della memoria riservata all'array A
    free(a);
    #endif

    return 0;
}

void mergeSort(int a[], int left, int right) 
{
    int center;
    if(left < right) {
        center = (left + right) / 2;
        mergeSort(a, left, center);
        mergeSort(a, center+1, right);
        merge(a, left, center, right);
    }
    return;
}

void merge(int *a, int left, int center, int right) 
{
    int i, j, k, *b;
    i = left;
    j = center + 1;
    k = 0;
    // L'array b ha dimensione right-left+1, cioè la dimensione dell'array a passato
    b = (int*)malloc(sizeof(int) * (right-left+1));

    while((i <= center) && (j <= right)) 
    {
        if(a[i] <= a[j])
        {
            b[k] = a[i];
            i++;
        }
        else
        {
            b[k] = a[j];
            j++;
        }
        k++;
    }

    // Rimangono da copiare gli eventuali elementi ancora da copiare
    while(i <= center) 
    {
        b[k] = a[i];
        i++;
        k++;
    }

    while(j <= right) 
    {
        b[k] = a[j];
        j++;
        k++;
    }

    // ricopiatura degli elementi dall'array di appoggio b all'array di appoggio a
    for(k = left; k <= right; k++) {
        a[k] = b[k - left];
    }

    // deallocazione della memoria allocata nella heap per l'array b
    free(b);

    return;
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