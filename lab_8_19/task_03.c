#include <stdio.h>
#include <stdlib.h>

static int is_prime(int x) {
    if (x < 2) return 0;
    for (int d = 2; d * d <= x; ++d)
        if (x % d == 0) return 0;
    return 1;
}

static int digits_strict_decrease(int x) {
    if (x < 0) return 0;
    int pow10 = 1;
    while (x >= pow10 * 10) pow10 *= 10;
    int prev = -1;
    while (pow10 > 0) {
        int d = (x / pow10) % 10;
        if (prev >= 0 && d >= prev) return 0;
        prev = d;
        pow10 /= 10;
    }
    return 1;
}

int main(void) {
    int n;
    printf("Введите размер массива (n): ");
    fflush(stdout);
    if (scanf("%d", &n) != 1 || n < 1) return 1;

    int *a = malloc((size_t)n * sizeof(int));
    printf("Введите %d целых элементов:\n", n);
    for (int i = 0; i < n; ++i) {
        printf("A[%d]: ", i + 1);
        fflush(stdout);
        if (scanf("%d", &a[i]) != 1) { free(a); return 1; }
    }

    int best_s = -1, best_len = n + 1, best_i = -1;
    int i = 0;
    while (i < n) {
        if (!is_prime(a[i])) { ++i; continue; }
        int j = i + 1;
        while (j < n && is_prime(a[j]) && digits_strict_decrease(a[j])) ++j;
        int len = j - i;
        if (len >= 1 && digits_strict_decrease(a[i])) {
            if (len < best_len || (len == best_len && i < best_s)) {
                best_len = len;
                best_s = i;
                best_i = i;
            }
        }
        i = j > i ? j : i + 1;
    }

    if (best_i < 0) {
        printf("Группа не найдена: ");
        for (int t = 0; t < n; ++t) { if (t) printf(" "); printf("%d", a[t]); }
        printf("\n");
        free(a);
        return 0;
    }

    int newn = n - best_len;
    int *b = malloc((size_t)newn * sizeof(int));
    int p = 0;
    for (int t = 0; t < n; ++t) {
        if (t < best_i || t >= best_i + best_len) b[p++] = a[t];
    }
    printf("Массив после удаления группы (%d элементов): ", p);
    for (int t = 0; t < p; ++t) { if (t) printf(" "); printf("%d", b[t]); }
    printf("\n");

    free(a); free(b);
    return 0;
}
