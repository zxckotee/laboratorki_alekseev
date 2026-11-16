#include <math.h>
#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#endif

double znachenie_f(double x) {
    double nom = log(fabs(cos(x - 2.0 * acos(-1.0))));
    double znam = sin(x) - 3.0 - pow(x, 0.2);
    if (znam == 0.0) {
        return 0.0 / 0.0;
    }
    double drob = 9.0 / sqrt(fabs(1.0 - exp(x))) / znam;
    return nom - drob;
}

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif

    double x;

    printf("Введите x: ");
    fflush(stdout);
    if (scanf("%lf", &x) != 1) {
        return 1;
    }

    double y = znachenie_f(x);
    if (y != y) {
        printf("Значение функции не определено при данном x.\n");
        return 0;
    }

    printf("f(x) = %.6f\n", y);
    return 0;
}