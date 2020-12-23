#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//#define MERGE_SORT

/* Variabili globali */
const unsigned int DIM = 7;
const unsigned int SEED = 18;
const unsigned int MAX_RAND = 100;
const unsigned int MIN_RAND = 10;

/* Funzioni */
void merge(int *a, int p, int q, int r);
void merge_sort(int *a, int p, int q);
void stampa_array(int *a);
void insertion_sort(int A[], int low, int high);
void generate_rand_array(int *a);
bool isSorted(int *a);

int main(int argc, char const *argv[])
{   
    int *a;
    a = (int*)malloc(sizeof(int)*DIM);
    
    // Generazione array casuale
    generate_rand_array(a);
    // Stampa a video dell'array non ordinato
    stampa_array(a);

    // Ordinamento dell'array
    #ifdef MERGE_SORT
    merge_sort(a, 0, DIM-1);
    #else
    insertion_sort(a, 0, DIM-1);
    #endif

    // Stampa dell'array ordinato
    stampa_array(a);

    // isSorted test
    printf("Is the array sorted?");
    if(isSorted(a))
        printf(" Yes, it is.\n");
    else
        printf(" No, it's not\n");

    return 0;
}

void stampa_array(int *a){
    unsigned int i;
    for(i = 0; i < DIM; ++i) {
        printf(" %d |", a[i]);
    }
    printf("\n");
    return;
}

/* procedura merge 
 * input:
 *  - a: array da ordinare
 *  - p: estremo sinistro array a
 *  - q: punto medio array a    
 *  - r: estremo destro array a
 * output: a ordinato in ordine crescente
 */
void merge(int *a, int p, int q, int r) {
    unsigned int n1, n2;
    unsigned int i, j, k; // indici per iterare sugli array
    int *left, *right;
    n1 = q-p+1; // dimensione di left
    n2 = r-q;   // dimensione di right
    
    left = (int*)malloc(sizeof(int)*n1);
    right = (int*)malloc(sizeof(int)*n2);

    for(i=0; i<n1; ++i) left[i] = a[p+i];
    for(j=0; j<n2; ++j) right[j] = a[q+j+1];

    i = j = 0;

    for(k = p; k <= r; ++k) {
        if(i < n1) {
            if(left[i] <= right[j] || j == n2) {
                // CopyFromL(i)
                a[k] = left[i];
                ++i;
            } else {
                // CopyFromR(j)
                a[k] = right[j];
                ++j;
            }
        } else {
            // CopyFromR(j)
            a[k] = right[j];
            ++j;
        }
    }
    return;
}

/* procedura merge_sort 
 * input:
 *  - a: array da ordinare
 *  - p: estremo sinistro array a
 *  - r: estremo destro array a
 * output: array a ordinato in ordine crescente.
 */
void merge_sort(int *a, int p, int r) {
    unsigned int q;
    if(p < r){
        q = ((p+r)/2);
        merge_sort(a, p, q);
        merge_sort(a, q+1, r);
        merge(a, p, q, r);
    } else {
        return;
    }
}

bool isSorted(int *a) {
    unsigned int i;
    bool is_sorted = false;
    for(i = 0; i < DIM-1; i++) {
        if(a[i] <= a[i+1])
            continue;
        else
            return false;
    }
    return true;
}

/* procedura insertion_sort 
 * input:
 *  - a: array da ordinare
 *  - low: estremo sinistro array a
 *  - high: estremo destro array a
 * output: array a ordinato in ordine crescente.
 */
void insertion_sort(int A[], int low, int high){
    for(int j = low; j <= high ; j++ ){
        int key = A[j]; // chiave di confronto se minore scambia
        int  i = j-1;
        while( i >= low && A[i] > key ){
            //int temp = A[i]; // temp -> variabile temporanea per scambio posizioni array
            A[i+1] = A[i];
            //A[i+1] = temp;
            i--; // decremento indice array
        }
        A[i+1] = key;
    }
    return;
}

void generate_rand_array(int *a){
	unsigned int i;
	for(i = 0; i < DIM; ++i) {
		a[i] = MIN_RAND + rand() % MAX_RAND; 
	}
}