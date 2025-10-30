#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int partition(int arr[], int left, int right) {
    int pivot = arr[right];
    int i = left;

    for (int j = left; j < right; j++) {
        if (arr[j] <= pivot) {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
        }
    }
    int temp = arr[i];
    arr[i] = arr[right];
    arr[right] = temp;
    return i;
}

int quickselect(int arr[], int left, int right, int k) {
    if (left == right)
        return arr[left];
    
    int pivotIndex = partition(arr, left, right);

    if (k == pivotIndex)
        return arr[k];
    else if (k < pivotIndex)
        return quickselect(arr, left, pivotIndex - 1, k);
    else
        return quickselect(arr, pivotIndex + 1, right, k);
}

void generarArreglo(int arr[], int n) {
    for (int i = 0; i < n; i++)
        arr[i] = rand() % (n * 10);
}

int main() {
    srand(time(NULL));
    printf("=== QuickSelect ===\n");

    int tamanos[] = {100, 1000, 100000};
    int num_tamanos = 3;

    for (int t = 0; t < num_tamanos; t++) {
        int n = tamanos[t];
        int *arr = malloc(n * sizeof(int));
        generarArreglo(arr, n);

        int k = rand() % n;
        clock_t inicio = clock();
        int resultado = quickselect(arr, 0, n - 1, k);
        clock_t fin = clock();

        double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
        printf("n=%d, k=%d, resultado=%d, tiempo=%.6fs\n", n, k, resultado, tiempo);
        free(arr);
    }
    return 0;
}