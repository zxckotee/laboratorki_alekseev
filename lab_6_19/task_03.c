#include <math.h>
#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#endif


static int digit_count(int x) {
    int n = 0;
    if (x == 0) {
        return 1;
    }
    while (x > 0) {
        ++n;
        x /= 10;
    }
    return n;
}

static int is_armstrong(int x) {
    if (x < 0) {
        return 0;
    }
    int k = digit_count(x);
    int t = x;
    long long sum = 0;
    while (t > 0) {
        int d = t % 10;
        sum += (long long)pow(d, k);
        t /= 10;
    }
    return sum == x;
}

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif

    int n;
    printf("Введите n: ");
    fflush(stdout);
    if (scanf("%d", &n) != 1 || n < 1) {
        return 1;
    }

    long double product = 1.0L;
    int found = 0;
    for (int x = 1; found < n; ++x) {
        if (is_armstrong(x)) {
            product *= (long double)x;
            ++found;
        }
    }

    printf("Произведение: %.6f\n", (double)product);
    return 0;
}
