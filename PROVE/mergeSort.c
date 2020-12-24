#include <stdio.h>
#include <stdlib.h>

const int dim = 10;


void generateRandomArray(int *a, const int dim);
void merge(int *a, int p, int r);
void mergeSort(int *a, int p, int q, int r);

int main(int argc, char const *argv[]) {
    
    



    return 0;
}

void generateRandomArray(int *a, const int dim) {
    for(unsigned int i = 0; i < dim; i++) {
        a[i] = rand() % RAND_MAX + 1;
    }
}