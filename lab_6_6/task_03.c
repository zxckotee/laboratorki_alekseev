#include <math.h>
#include <stdio.h>

static int is_palindrome(int x) {
    if (x < 0) {
        return 0;
    }
    int orig = x;
    int rev = 0;
    int t = x;
    while (t > 0) {
        rev = rev * 10 + t % 10;
        t /= 10;
    }
    if (x == 0) {
        return 1;
    }
    return orig == rev;
}

int main(void) {
    int n;

    printf("Введите n (100 <= n <= 1000): ");
    fflush(stdout);
    if (scanf("%d", &n) != 1 || n < 100 || n > 1000) {
        return 1;
    }

    long long sum = 0;
    int count = 0;
    for (int x = 1; count < n; ++x) {
        if (is_palindrome(x)) {
            sum += x;
            ++count;
        }
    }

    printf("Корень из суммы: %.6f\n", sqrt((double)sum));
    return 0;
}
