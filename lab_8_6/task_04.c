#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#endif


static int digit_sum(int x) {
    if (x < 0) {
        x = -x;
    }
    int s = 0;
    while (x > 0) {
        s += x % 10;
        x /= 10;
    }
    return s;
}

static int is_palindrome(int x) {
    if (x < 0) {
        return 0;
    }
    int o = x, r = 0;
    if (x == 0) {
        return 1;
    }
    while (x > 0) {
        r = r * 10 + x % 10;
        x /= 10;
    }
    return o == r;
}

static int is_prime(int x) {
    if (x < 2) {
        return 0;
    }
    for (int d = 2; d * d <= x; ++d) {
        if (x % d == 0) {
            return 0;
        }
    }
    return 1;
}

typedef struct {
    int val;
    int sum;
} Item;

static int cmp_item(const void *a, const void *b) {
    const Item *ia = a;
    const Item *ib = b;
    if (ia->sum != ib->sum) {
        return ia->sum - ib->sum;
    }
    return ia->val - ib->val;
}

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif

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

    int last_pal = -1;
    int first_prime = n;
    for (int i = 0; i < n; ++i) {
        if (is_palindrome(a[i])) {
            last_pal = i;
        }
    }
    for (int i = 0; i < n; ++i) {
        if (is_prime(a[i])) {
            first_prime = i;
            break;
        }
    }

    if (last_pal < 0 || first_prime >= n || last_pal + 1 >= first_prime) {
        printf("Нет подходящего интервала, массив: ");
        for (int i = 0; i < n; ++i) {
            if (i) {
                printf(" ");
            }
            printf("%d", a[i]);
        }
        printf("\n");
        free(a);
        return 0;
    }

    int left = last_pal + 1;
    int right = first_prime;
    int m = right - left;
    Item *items = malloc((size_t)m * sizeof(Item));
    for (int i = 0; i < m; ++i) {
        items[i].val = a[left + i];
        items[i].sum = digit_sum(a[left + i]);
    }
    qsort(items, (size_t)m, sizeof(Item), cmp_item);

    int *out = malloc((size_t)n * sizeof(int));
    int p = 0;
    for (int i = 0; i < left; ++i) {
        out[p++] = a[i];
    }
    for (int i = 0; i < m; ++i) {
        out[p++] = items[i].val;
    }
    for (int i = right; i < n; ++i) {
        out[p++] = a[i];
    }

    printf("Результирующий массив: ");
    for (int i = 0; i < p; ++i) {
        if (i) {
            printf(" ");
        }
        printf("%d", out[i]);
    }
    printf("\n");

    free(a);
    free(items);
    free(out);
    return 0;
}
