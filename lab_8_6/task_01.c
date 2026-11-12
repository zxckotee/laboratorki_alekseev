#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#endif


int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif

    int n, m;
    printf("Введите размер массива X (n): ");
    fflush(stdout);
    if (scanf("%d", &n) != 1 || n < 1) {
        return 1;
    }
    double *x = malloc((size_t)n * sizeof(double));
    if (!x) {
        return 1;
    }
    printf("Введите %d вещественных элементов X:\n", n);
    for (int i = 0; i < n; ++i) {
        printf("X[%d]: ", i + 1);
        fflush(stdout);
        if (scanf("%lf", &x[i]) != 1) {
            free(x);
            return 1;
        }
    }

    double sum_pos = 0.0;
    for (int i = 0; i < n; ++i) {
        if (x[i] > 0.0) {
            sum_pos += x[i];
        }
    }

    double prod = 1.0;
    int has = 0;
    int half = n / 2;
    for (int i = half; i < n; ++i) {
        if ((i + 1) % 2 == 1) {
            prod *= x[i];
            has = 1;
        }
    }
    if (!has) {
        prod = 0.0;
    }

    printf("Сумма положительных: %.6f\n", sum_pos);
    printf("Произведение (2-я половина, нечетный индекс): %.6f\n", prod);

    printf("Введите размер массива Y (m): ");
    fflush(stdout);
    if (scanf("%d", &m) != 1 || m < 1) {
        free(x);
        return 1;
    }
    double *y = malloc((size_t)m * sizeof(double));
    if (!y) {
        free(x);
        return 1;
    }
    printf("Введите %d вещественных элементов Y:\n", m);
    for (int i = 0; i < m; ++i) {
        printf("Y[%d]: ", i + 1);
        fflush(stdout);
        if (scanf("%lf", &y[i]) != 1) {
            free(x);
            free(y);
            return 1;
        }
    }

    int cap = n + m;
    double *neg = malloc((size_t)cap * sizeof(double));
    double *zer = malloc((size_t)cap * sizeof(double));
    double *pos = malloc((size_t)cap * sizeof(double));
    int cn = 0, cz = 0, cp = 0;

    for (int i = 0; i < n + m; ++i) {
        double v = (i < n) ? x[i] : y[i - n];
        if (v < 0.0) {
            neg[cn++] = v;
        } else if (v == 0.0) {
            zer[cz++] = v;
        } else {
            pos[cp++] = v;
        }
    }

    free(x);
    free(y);

    int zlen = cn + cz + cp;
    double *z = malloc((size_t)zlen * sizeof(double));
    int zi = 0;
    for (int i = 0; i < cn; ++i) {
        z[zi++] = neg[i];
    }
    for (int i = 0; i < cz; ++i) {
        z[zi++] = zer[i];
    }
    for (int i = 0; i < cp; ++i) {
        z[zi++] = pos[i];
    }

    int imax = 0;
    for (int i = 1; i < zlen; ++i) {
        if (z[i] > z[imax]) {
            imax = i;
        }
    }
    for (int i = imax; i < zlen - 1; ++i) {
        z[i] = z[i + 1];
    }
    --zlen;

    printf("Массив Z после удаления максимума (%d элементов): ", zlen);
    for (int i = 0; i < zlen; ++i) {
        if (i) {
            printf(" ");
        }
        printf("%.6f", z[i]);
    }
    printf("\n");

    free(neg);
    free(zer);
    free(pos);
    free(z);
    return 0;
}
