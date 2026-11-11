#include <math.h>
#include <stdio.h>

static double compute_y(double x, int n) {
    double y = 0.0;
    for (int k = 1; k <= n; ++k) {
        double sign = (k % 2 == 1) ? -1.0 : 1.0;
        double denom = (double)k * pow(2.0, k);
        double xp = pow(x, k + 1);
        y += sign * xp / denom;
    }
    return y;
}

int main(void) {
    int n;
    double x;

    printf("Введите натуральное n: ");
    fflush(stdout);
    if (scanf("%d", &n) != 1 || n < 1) {
        return 1;
    }

    printf("Введите x (|x| < 1): ");
    fflush(stdout);
    if (scanf("%lf", &x) != 1 || fabs(x) >= 1.0) {
        return 1;
    }

    printf("y = %.6f\n", compute_y(x, n));
    return 0;
}
