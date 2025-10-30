#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long merge_and_count(int arr[], int temp[], int left, int mid, int right) {
    int i = left, j = mid, k = left;
    long long inv_count = 0;

    while ((i <= mid - 1) && (j <= right)) {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else {
            temp[k++] = arr[j++];
            inv_count += (mid - i);
        }
    }

    while (i <= mid - 1)
        temp[k++] = arr[i++];

    while (j <= right)
        temp[k++] = arr[j++];

    for (i = left; i <= right; i++)
        arr[i] = temp[i];

    return inv_count;
}

long long merge_sort_count(int arr[], int temp[], int left, int right) {
    long long inv_count = 0;
    if (right > left) {
        int mid = (right + left) / 2;
        inv_count += merge_sort_count(arr, temp, left, mid);
        inv_count += merge_sort_count(arr, temp, mid + 1, right);
        inv_count += merge_and_count(arr, temp, left, mid + 1, right);
    }
    return inv_count;
}

void generarArreglo(int arr[], int n) {
    for (int i = 0; i < n; i++)
        arr[i] = rand() % (n * 10);
}

int main() {
    srand(time(NULL));
    printf("=== Contar Inversiones ===\n");

    int tamanos[] = {100, 1000, 100000};
    int num_tamanos = 3;

    for (int t = 0; t < num_tamanos; t++) {
        int n = tamanos[t];
        int *arr = malloc(n * sizeof(int));
        int *temp = malloc(n * sizeof(int));
        generarArreglo(arr, n);

        clock_t inicio = clock();
        long long inv = merge_sort_count(arr, temp, 0, n - 1);
        clock_t fin = clock();

        double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
        printf("n=%d, inversiones=%lld, tiempo=%.6fs\n", n, inv, tiempo);

        free(arr);
        free(temp);
    }

    return 0;
}