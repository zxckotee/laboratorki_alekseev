#include <math.h>
#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#endif


static double compute_y(double x, int n) {
    double y = 0.0;
    for (int k = 1; k <= n; ++k) {
        double sign = (k % 2 == 1) ? -1.0 : 1.0;
        y += sign * pow(x, 2.0 * k) / (2.0 * k + 1.0);
    }
    return y;
}

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif

    int n;
    double x;
    printf("Введите натуральное n: ");
    fflush(stdout);
    if (scanf("%d", &n) != 1 || n < 1) {
        return 1;
    }
    printf("Введите x: ");
    fflush(stdout);
    if (scanf("%lf", &x) != 1) {
        return 1;
    }

    printf("y = %.6f\n", compute_y(x, n));
    return 0;
}
