#include <stdio.h>

static int is_palindrome(int x) {
    if (x < 0) {
        return 0;
    }
    int orig = x;
    int rev = 0;
    if (x == 0) {
        return 1;
    }
    while (x > 0) {
        rev = rev * 10 + x % 10;
        x /= 10;
    }
    return orig == rev;
}

int main(void) {
    int need;
    if (scanf("%d", &need) != 1 || need < 1) {
        return 1;
    }

    int pal_count = 0;
    int value;
    int first = 1;
    while (pal_count < need && scanf("%d", &value) == 1) {
        if (!first) {
            printf(" ");
        }
        printf("%o", value);
        first = 0;
        if (is_palindrome(value)) {
            ++pal_count;
        }
    }
    printf("\n");
    return pal_count == need ? 0 : 1;
}
