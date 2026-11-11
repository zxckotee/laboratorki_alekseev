#include <stdio.h>

static int is_prime(int x) {
    if (x < 2) {
        return 0;
    }
    if (x == 2) {
        return 1;
    }
    if (x % 2 == 0) {
        return 0;
    }
    for (int d = 3; d * d <= x; d += 2) {
        if (x % d == 0) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    int a, b, n;
    if (scanf("%d %d %d", &a, &b, &n) != 3 || n < 1 || a > b) {
        return 1;
    }

    int found = 0;
    for (int x = a; x <= b && found < n; ++x) {
        if (is_prime(x)) {
            if (found > 0) {
                printf(" ");
            }
            printf("%d", x);
            ++found;
        }
    }
    printf("\n");
    return found == n ? 0 : 0;
}
