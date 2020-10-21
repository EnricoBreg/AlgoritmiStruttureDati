#include <stdio.h>
#include <stdlib.h>

#define DIM 6

void stampaArray(int A[]) {
    int i;
    for(i = 0; i < DIM; i++) {
        printf("%d | ", A[i]);
    }
    printf("\n");
    return;
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



int main() {

    int A[DIM] = {29, 34, 77, 10, 28, 96};
    int p, q, r;
    p = 0;
    r = (int)DIM;
    q = (r - p) / 2;

    stampaArray(A);

    merge(A, p, q, r);

    stampaArray(A);

    return 0;

}