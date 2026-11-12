#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#endif


static int is_perfect(int x) {
    if (x < 2) {
        return 0;
    }
    int sum = 1;
    for (int d = 2; d * d <= x; ++d) {
        if (x % d == 0) {
            sum += d;
            if (d != x / d) {
                sum += x / d;
            }
        }
    }
    return sum == x;
}

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif

    int n;
    printf("Введите количество совершенных чисел n: ");
    fflush(stdout);
    if (scanf("%d", &n) != 1 || n < 1) {
        return 1;
    }

    long long sum = 0;
    int found = 0;
    for (int x = 2; found < n; ++x) {
        if (is_perfect(x)) {
            printf("%d\n", x);
            sum += x;
            ++found;
        }
    }

    printf("Сумма: %lld\n", sum);
    printf("Среднее: %.6f\n", (double)sum / (double)n);
    return 0;
}
