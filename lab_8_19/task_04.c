#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#endif


static int digit_sum(int x) {
    if (x < 0) x = -x;
    int s = 0;
    while (x > 0) { s += x % 10; x /= 10; }
    return s;
}

static int is_palindrome(int x) {
    if (x < 0) return 0;
    int o = x, r = 0;
    if (x == 0) return 1;
    while (x > 0) { r = r * 10 + x % 10; x /= 10; }
    return o == r;
}

typedef struct { int val; int sum; } Item;

static int cmp_item_desc(const void *a, const void *b) {
    const Item *ia = a, *ib = b;
    if (ia->sum != ib->sum) return ib->sum - ia->sum;
    return ib->val - ia->val;
}

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif

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

    int pal_pos[256];
    int pc = 0;
    for (int i = 0; i < n; ++i) {
        if (is_palindrome(a[i]) && pc < 256) pal_pos[pc++] = i;
    }

    if (pc < 2) {
        printf("Недостаточно палиндромов, массив: ");
        for (int i = 0; i < n; ++i) { if (i) printf(" "); printf("%d", a[i]); }
        printf("\n");
        free(a);
        return 0;
    }

    int left = pal_pos[pc - 2] + 1;
    int right = pal_pos[pc - 1];
    if (left >= right) {
        printf("Пустой интервал, массив: ");
        for (int i = 0; i < n; ++i) { if (i) printf(" "); printf("%d", a[i]); }
        printf("\n");
        free(a);
        return 0;
    }

    int m = right - left;
    Item *items = malloc((size_t)m * sizeof(Item));
    for (int i = 0; i < m; ++i) {
        items[i].val = a[left + i];
        items[i].sum = digit_sum(a[left + i]);
    }
    qsort(items, (size_t)m, sizeof(Item), cmp_item_desc);

    int out[512];
    int p = 0;
    for (int i = 0; i < left; ++i) out[p++] = a[i];
    for (int i = 0; i < m; ++i) out[p++] = items[i].val;
    for (int i = right; i < n; ++i) out[p++] = a[i];

    printf("Результирующий массив: ");
    for (int i = 0; i < p; ++i) { if (i) printf(" "); printf("%d", out[i]); }
    printf("\n");

    free(a); free(items);
    return 0;
}
