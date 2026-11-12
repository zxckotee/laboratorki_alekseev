#include <stdio.h>
#include <stdlib.h>

static int is_odd(int x) {
    return x % 2 != 0;
}

static int group_strict_decrease(int *a, int len) {
    if (len < 1) {
        return 0;
    }
    for (int i = 1; i < len; ++i) {
        if (!is_odd(a[i - 1]) || !is_odd(a[i]) || a[i] >= a[i - 1]) {
            return 0;
        }
    }
    return is_odd(a[0]);
}

int main(void) {
    int n;
    printf("Введите размер массива (n): ");
    fflush(stdout);
    if (scanf("%d", &n) != 1 || n < 1) {
        return 1;
    }
    int *a = malloc((size_t)n * sizeof(int));
    printf("Введите %d целых элементов:\n", n);
    for (int i = 0; i < n; ++i) {
        printf("A[%d]: ", i + 1);
        fflush(stdout);
        if (scanf("%d", &a[i]) != 1) {
            free(a);
            return 1;
        }
    }

    int last_start = -1;
    int last_len = 0;
    int i = 0;
    while (i < n) {
        if (!is_odd(a[i])) {
            ++i;
            continue;
        }
        int j = i + 1;
        while (j < n && is_odd(a[j]) && a[j] < a[j - 1]) {
            ++j;
        }
        int len = j - i;
        if (len >= 1 && group_strict_decrease(a + i, len)) {
            last_start = i;
            last_len = len;
        }
        i = (len >= 1) ? j : i + 1;
    }

    if (last_start < 0) {
        printf("Группа не найдена, массив без изменений: ");
        for (int t = 0; t < n; ++t) {
            if (t) {
                printf(" ");
            }
            printf("%d", a[t]);
        }
        printf("\n");
        free(a);
        return 0;
    }

    int newn = n - last_len;
    int *b = malloc((size_t)newn * sizeof(int));
    int p = 0;
    for (int t = 0; t < n; ++t) {
        if (t < last_start || t >= last_start + last_len) {
            b[p++] = a[t];
        }
    }

    printf("Массив после удаления группы (%d элементов): ", newn);
    for (int t = 0; t < newn; ++t) {
        if (t) {
            printf(" ");
        }
        printf("%d", b[t]);
    }
    printf("\n");

    free(a);
    free(b);
    return 0;
}
