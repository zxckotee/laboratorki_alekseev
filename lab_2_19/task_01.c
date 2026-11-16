#include <math.h>
#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#endif

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif

    double a1, b1, a2, b2;

    printf("Введите a1: ");
    fflush(stdout);
    if (scanf("%lf", &a1) != 1) {
        return 1;
    }
    printf("Введите b1: ");
    fflush(stdout);
    if (scanf("%lf", &b1) != 1) {
        return 1;
    }
    printf("Введите a2: ");
    fflush(stdout);
    if (scanf("%lf", &a2) != 1) {
        return 1;
    }
    printf("Введите b2: ");
    fflush(stdout);
    if (scanf("%lf", &b2) != 1) {
        return 1;
    }

    if (fabs(a1 - a2) < 1e-9 && fabs(b1 - b2) < 1e-9) {
        printf("Прямые совпадают.\n");
    } else if (fabs(a1 - a2) < 1e-9) {
        printf("Прямые параллельны (не совпадают).\n");
    } else {
        printf("Прямые пересекаются.\n");
        double x = (b2 - b1) / (a1 - a2);
        double y = a1 * x + b1;
        printf("Точка пересечения: x = %.6f, y = %.6f\n", x, y);
    }

    return 0;
}