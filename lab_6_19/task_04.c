#include <math.h>
#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#endif


static double series_s(double x, int n) {
    double s = -1.0;
    for (int k = 1; k <= n; ++k) {
        long long fact = 1;
        for (int i = 2; i <= k; ++i) {
            fact *= i;
        }
        double term = (2.0 * k - 1.0) * pow(x, k) / (pow(2.0, k) * (double)fact);
        s += term;
    }
    return s;
}

static double y_func(double x) {
    return (x - 1.0) * exp(x / 2.0);
}

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif

    int n;
    double h;
    printf("Введите количество слагаемых n: ");
    fflush(stdout);
    if (scanf("%d", &n) != 1 || n < 1) {
        return 1;
    }
    printf("Введите шаг h: ");
    fflush(stdout);
    if (scanf("%lf", &h) != 1 || h <= 0.0) {
        return 1;
    }

    printf("x\tS(x)\t\tY(x)\n");
    for (double x = 0.0; x <= 1.0 + 1e-9; x += h) {
        if (x > 1.0) {
            x = 1.0;
        }
        printf("%.4f\t%.6f\t%.6f\n", x, series_s(x, n), y_func(x));
        if (fabs(x - 1.0) < 1e-9) {
            break;
        }
    }
    return 0;
}
