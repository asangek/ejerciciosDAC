#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct {
    double x, y;
} Punto;

double distancia(Punto a, Punto b) {
    return sqrt((a.x - b.x)(a.x - b.x) + (a.y - b.y)(a.y - b.y));
}

int compararX(const void *a, const void *b) {
    Punto *p1 = (Punto *)a;
    Punto *p2 = (Punto *)b;
    return (p1->x > p2->x) - (p1->x < p2->x);
}

int compararY(const void *a, const void *b) {
    Punto *p1 = (Punto *)a;
    Punto *p2 = (Punto *)b;
    return (p1->y > p2->y) - (p1->y < p2->y);
}

double min(double a, double b) {
    return (a < b) ? a : b;
}

double fuerzaBruta(Punto puntos[], int n) {
    double minDist = 1e9;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double d = distancia(puntos[i], puntos[j]);
            if (d < minDist)
                minDist = d;
        }
    }
    return minDist;
}

double minBanda(Punto banda[], int size, double d) {
    double minDist = d;
    qsort(banda, size, sizeof(Punto), compararY);
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size && (banda[j].y - banda[i].y) < minDist; ++j) {
            double dist = distancia(banda[i], banda[j]);
            if (dist < minDist)
                minDist = dist;
        }
    }
    return minDist;
}

double parCercanoRec(Punto puntos[], int n) {
    if (n <= 3)
        return fuerzaBruta(puntos, n);

    int mid = n / 2;
    Punto midPoint = puntos[mid];

    double dIzq = parCercanoRec(puntos, mid);
    double dDer = parCercanoRec(puntos + mid, n - mid);
    double d = min(dIzq, dDer);

    Punto *banda = malloc(n * sizeof(Punto));
    int j = 0;
    for (int i = 0; i < n; i++)
        if (fabs(puntos[i].x - midPoint.x) < d)
            banda[j++] = puntos[i];

    double dBanda = minBanda(banda, j, d);
    free(banda);

    return min(d, dBanda);
}

double parCercano(Punto puntos[], int n) {
    qsort(puntos, n, sizeof(Punto), compararX);
    return parCercanoRec(puntos, n);
}

void generarPuntos(Punto puntos[], int n) {
    for (int i = 0; i < n; i++) {
        puntos[i].x = (double)rand() / RAND_MAX * 1000.0;
        puntos[i].y = (double)rand() / RAND_MAX * 1000.0;
    }
}

int main() {
    srand(time(NULL));
    printf("=== Par de puntos más cercanos ===\n");

    int tamanos[] = {10, 100, 1000, 100000};
    int num_tamanos = 4;

    for (int t = 0; t < num_tamanos; t++) {
        int n = tamanos[t];
        Punto *puntos = malloc(n * sizeof(Punto));
        generarPuntos(puntos, n);

        clock_t inicio = clock();
        double d = parCercano(puntos, n);
        clock_t fin = clock();

        double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
        printf("n=%d, distancia mínima=%.6f, tiempo=%.6fs\n", n, d, tiempo);

        free(puntos);
    }

    return 0;
}