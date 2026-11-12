#include <math.h>
#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#endif


static double sinh_ref(double x) {
    return (exp(x) - exp(-x)) / 2.0;
}

static double series_sinh(double x, int n) {
    double s = 0.0;
    for (int k = 1; k <= n; ++k) {
        int power = 2 * k - 1;
        double term = pow(x, power);
        long long fact = 1;
        for (int f = 2; f <= power; ++f) {
            fact *= f;
        }
        s += term / (double)fact;
    }
    return s;
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
        printf("%.4f\t%.6f\t%.6f\n", x, series_sinh(x, n), sinh_ref(x));
        if (fabs(x - 1.0) < 1e-9) {
            break;
        }
    }
    return 0;
}
