#include <stdio.h>

#define MAX_VALUES 10000

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

    printf("Введите количество палиндромов n: ");
    fflush(stdout);
    if (scanf("%d", &need) != 1 || need < 1) {
        return 1;
    }

    int values[MAX_VALUES];
    int count = 0;
    int pal_count = 0;

    while (pal_count < need) {
        printf("Введите целое число: ");
        fflush(stdout);
        int value;
        if (scanf("%d", &value) != 1) {
            return 1;
        }
        if (count < MAX_VALUES) {
            values[count++] = value;
        }
        if (is_palindrome(value)) {
            ++pal_count;
        }
    }

    printf("В восьмеричной системе счисления: ");
    for (int i = 0; i < count; ++i) {
        if (i > 0) {
            printf(" ");
        }
        printf("%o", values[i]);
    }
    printf("\n");
    return 0;
}
