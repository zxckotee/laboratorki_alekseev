#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#endif


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
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif

    int a, b, n;

    printf("Введите нижнюю границу диапазона a: ");
    fflush(stdout);
    if (scanf("%d", &a) != 1) {
        return 1;
    }

    printf("Введите верхнюю границу диапазона b: ");
    fflush(stdout);
    if (scanf("%d", &b) != 1) {
        return 1;
    }

    printf("Введите количество простых чисел n: ");
    fflush(stdout);
    if (scanf("%d", &n) != 1 || n < 1 || a > b) {
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
    return 0;
}
