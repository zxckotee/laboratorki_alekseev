#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#endif


static int has_digit_zero(int x) {
    if (x == 0) {
        return 1;
    }
    if (x < 0) {
        x = -x;
    }
    while (x > 0) {
        if (x % 10 == 0) {
            return 1;
        }
        x /= 10;
    }
    return 0;
}

static int is_composite(int x) {
    if (x < 4) {
        return 0;
    }
    for (int d = 2; d * d <= x; ++d) {
        if (x % d == 0) {
            return 1;
        }
    }
    return 0;
}

static int cmp_int(const void *a, const void *b) {
    int ia = *(const int *)a;
    int ib = *(const int *)b;
    return (ia > ib) - (ia < ib);
}

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif

    int n, k;
    printf("Введите размер массива X (n): ");
    fflush(stdout);
    if (scanf("%d", &n) != 1 || n < 1) {
        return 1;
    }
    int *x = malloc((size_t)n * sizeof(int));
    printf("Введите %d целых элементов X:\n", n);
    for (int i = 0; i < n; ++i) {
        printf("X[%d]: ", i + 1);
        fflush(stdout);
        if (scanf("%d", &x[i]) != 1) {
            free(x);
            return 1;
        }
    }

    printf("Введите размер массива Y (k): ");
    fflush(stdout);
    if (scanf("%d", &k) != 1 || k < 1) {
        free(x);
        return 1;
    }
    int *y = malloc((size_t)k * sizeof(int));
    printf("Введите %d целых элементов Y:\n", k);
    for (int i = 0; i < k; ++i) {
        printf("Y[%d]: ", i + 1);
        fflush(stdout);
        if (scanf("%d", &y[i]) != 1) {
            free(x);
            free(y);
            return 1;
        }
    }

    int cap = n + k;
    int *z = malloc((size_t)cap * sizeof(int));
    int zlen = 0;
    for (int i = 0; i < n; ++i) {
        if (!has_digit_zero(x[i])) {
            z[zlen++] = x[i];
        }
    }
    for (int i = 0; i < k; ++i) {
        if (is_composite(y[i])) {
            z[zlen++] = y[i];
        }
    }

    int *odds = malloc((size_t)zlen * sizeof(int));
    int oc = 0;
    for (int i = 0; i < zlen; ++i) {
        if (z[i] % 2 != 0) {
            odds[oc++] = z[i];
        }
    }
    qsort(odds, (size_t)oc, sizeof(int), cmp_int);
    int take = oc < 5 ? oc : 5;
    int start = oc - take;

    printf("Пять наибольших нечетных в Z: ");
    for (int i = 0; i < take; ++i) {
        if (i) {
            printf(" ");
        }
        printf("%d", odds[start + i]);
    }
    printf("\n");

    qsort(x, (size_t)n, sizeof(int), cmp_int);
    qsort(y, (size_t)k, sizeof(int), cmp_int);
    qsort(z, (size_t)zlen, sizeof(int), cmp_int);

    printf("X (сорт.): ");
    for (int i = 0; i < n; ++i) {
        if (i) {
            printf(" ");
        }
        printf("%d", x[i]);
    }
    printf("\nY (сорт.): ");
    for (int i = 0; i < k; ++i) {
        if (i) {
            printf(" ");
        }
        printf("%d", y[i]);
    }
    printf("\nZ (сорт.): ");
    for (int i = 0; i < zlen; ++i) {
        if (i) {
            printf(" ");
        }
        printf("%d", z[i]);
    }
    printf("\n");

    free(x);
    free(y);
    free(z);
    free(odds);
    return 0;
}
