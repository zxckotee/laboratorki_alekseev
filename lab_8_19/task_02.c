#include <stdio.h>
#include <stdlib.h>

static int from_base_representation(int code, int base) {
    int sign = 1;
    if (code < 0) { sign = -1; code = -code; }
    int result = 0;
    int pow = 1;
    while (code > 0) {
        int d = code % 10;
        if (d >= base) return 0;
        result += d * pow;
        pow *= base;
        code /= 10;
    }
    return sign * result;
}

static int digit_sum(int x) {
    if (x < 0) x = -x;
    int s = 0;
    while (x > 0) { s += x % 10; x /= 10; }
    return s;
}

static int cmp_desc(const void *a, const void *b) {
    int ia = *(const int *)a, ib = *(const int *)b;
    return (ib > ia) - (ib < ia);
}

int main(void) {
    int n, k;
    printf("Введите размер массива X (n): ");
    fflush(stdout);
    if (scanf("%d", &n) != 1 || n < 1) return 1;

    int *z = malloc((size_t)(n + 256) * sizeof(int));
    int zlen = 0;

    printf("Введите %d чисел в пятеричной записи:\n", n);
    for (int i = 0; i < n; ++i) {
        int code;
        printf("X[%d]: ", i + 1);
        fflush(stdout);
        if (scanf("%d", &code) != 1) { free(z); return 1; }
        z[zlen++] = from_base_representation(code, 5);
    }

    printf("Введите размер массива Y (k): ");
    fflush(stdout);
    if (scanf("%d", &k) != 1 || k < 1) { free(z); return 1; }

    printf("Введите %d чисел в шестеричной записи:\n", k);
    for (int i = 0; i < k; ++i) {
        int code;
        printf("Y[%d]: ", i + 1);
        fflush(stdout);
        if (scanf("%d", &code) != 1) { free(z); return 1; }
        z[zlen++] = from_base_representation(code, 6);
    }

    int *cand = malloc((size_t)zlen * sizeof(int));
    int cc = 0;
    for (int i = 0; i < zlen; ++i) {
        if (digit_sum(z[i]) % 2 != 0) cand[cc++] = z[i];
    }
    qsort(cand, (size_t)cc, sizeof(int), cmp_desc);

    int take = cc < 5 ? cc : 5;
    printf("Z (десятичный, %d элементов): ", zlen);
    for (int i = 0; i < zlen; ++i) {
        if (i) printf(" ");
        printf("%d", z[i]);
    }
    printf("\nПять наибольших с нечетной суммой цифр: ");
    for (int i = 0; i < take; ++i) {
        if (i) printf(" ");
        printf("%d", cand[i]);
    }
    printf("\n");

    free(z); free(cand);
    return 0;
}
