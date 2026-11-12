#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#endif


int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif

    int n, k;
    printf("Введите размер массива X (n): ");
    fflush(stdout);
    if (scanf("%d", &n) != 1 || n < 1) return 1;

    int *x = malloc((size_t)n * sizeof(int));
    printf("Введите %d целых элементов X:\n", n);
    for (int i = 0; i < n; ++i) {
        printf("X[%d]: ", i + 1);
        fflush(stdout);
        if (scanf("%d", &x[i]) != 1) { free(x); return 1; }
    }

    long long prod7 = 1;
    int has7 = 0;
    for (int i = 0; i < n; ++i) {
        if (x[i] != 0 && x[i] % 7 == 0) {
            prod7 *= x[i];
            has7 = 1;
        }
    }
    if (!has7) prod7 = 0;

    int fe = -1, le = -1;
    for (int i = 0; i < n; ++i) {
        if (x[i] % 2 == 0) {
            if (fe < 0) fe = i;
            le = i;
        }
    }
    int between = 0;
    if (fe >= 0 && le > fe) between = le - fe - 1;

    printf("Произведение кратных 7: %lld\n", prod7);
    printf("Количество между первым и последним четным: %d\n", between);

    printf("Введите k (число положительных для Y): ");
    fflush(stdout);
    if (scanf("%d", &k) != 1 || k < 0) { free(x); return 1; }

    int *y = malloc((size_t)n * sizeof(int));
    int ylen = 0;
    for (int i = 0; i < n && ylen < k; ++i) {
        if (x[i] > 0) y[ylen++] = x[i];
    }

    printf("Массив Y (%d): ", ylen);
    for (int i = 0; i < ylen; ++i) {
        if (i) printf(" ");
        printf("%d", y[i]);
    }
    printf("\n");

    double mean = 0.0;
    for (int i = 0; i < n; ++i) mean += x[i];
    mean /= (double)n;

    int best = 0;
    double best_d = fabs(x[0] - mean);
    for (int i = 1; i < n; ++i) {
        double d = fabs(x[i] - mean);
        if (d < best_d - 1e-9 || (fabs(d - best_d) < 1e-9 && i < best)) {
            best_d = d;
            best = i;
        }
    }
    int *xn = malloc((size_t)(n - 1) * sizeof(int));
    int p = 0;
    for (int i = 0; i < n; ++i) {
        if (i != best) xn[p++] = x[i];
    }
    printf("X после удаления элемента, ближайшего к среднему (%.3f):\n", mean);
    for (int i = 0; i < p; ++i) {
        if (i) printf(" ");
        printf("%d", xn[i]);
    }
    printf("\n");

    free(x); free(y); free(xn);
    return 0;
}
