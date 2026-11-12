#include <math.h>
#include <stdio.h>

static int solve_quadratic(double a, double b, double c, double *r1, double *r2) {
    if (fabs(a) < 1e-12) {
        return 0;
    }
    double d = b * b - 4.0 * a * c;
    if (d < 0.0) {
        return 0;
    }
    if (d == 0.0) {
        *r1 = -b / (2.0 * a);
        return 1;
    }
    double sd = sqrt(d);
    *r1 = (-b - sd) / (2.0 * a);
    *r2 = (-b + sd) / (2.0 * a);
    return 2;
}

int main(void) {
    int n;
    printf("Введите количество парабол N: ");
    fflush(stdout);
    if (scanf("%d", &n) != 1 || n < 1) {
        return 1;
    }

    double sum = 0.0;
    int root_count = 0;

    for (int i = 1; i <= n; ++i) {
        double a, b, c;
        printf("Введите коэффициент a для параболы %d: ", i);
        fflush(stdout);
        if (scanf("%lf", &a) != 1) {
            return 1;
        }
        printf("Введите коэффициент b для параболы %d: ", i);
        fflush(stdout);
        if (scanf("%lf", &b) != 1) {
            return 1;
        }
        printf("Введите коэффициент c для параболы %d: ", i);
        fflush(stdout);
        if (scanf("%lf", &c) != 1) {
            return 1;
        }

        double x1 = 0.0;
        double x2 = 0.0;
        int k = solve_quadratic(a, b, c, &x1, &x2);
        if (k >= 1) {
            sum += x1;
            ++root_count;
        }
        if (k == 2) {
            sum += x2;
            ++root_count;
        }
    }

    if (root_count == 0) {
        printf("Действительных точек пересечения с осью OX нет.\n");
        return 0;
    }

    printf("Среднее арифметическое абсцисс: %.6f\n", sum / (double)root_count);
    return 0;
}
