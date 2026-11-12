#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#endif


static int sum_proper_divisors(int x) {
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
    return sum;
}

static int is_abundant(int x) {
    return x > 1 && sum_proper_divisors(x) > x;
}

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif

    int need;
    printf("Введите номер избыточного числа n: ");
    fflush(stdout);
    if (scanf("%d", &need) != 1 || need < 1) {
        return 1;
    }

    int abundant = 0;
    int max1 = 0;
    int max2 = 0;
    int count = 0;

    while (abundant < need) {
        int x;
        printf("Введите целое число: ");
        fflush(stdout);
        if (scanf("%d", &x) != 1) {
            return 1;
        }
        ++count;
        if (x > max1) {
            max2 = max1;
            max1 = x;
        } else if (x > max2) {
            max2 = x;
        }
        if (is_abundant(x)) {
            ++abundant;
        }
    }

    if (count < 2) {
        printf("Недостаточно чисел для второго максимума.\n");
        return 0;
    }

    printf("Второе по величине число: %d\n", max2);
    return 0;
}
