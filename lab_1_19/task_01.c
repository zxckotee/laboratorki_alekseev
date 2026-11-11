#include <math.h>
#include <stdio.h>

int main(void) {
    double a, b;
    if (scanf("%lf %lf", &a, &b) != 2) {
        return 1;
    }

    double c = hypot(a, b);
    const double rad2deg = 180.0 / acos(-1.0);
    double alpha = atan2(a, b) * rad2deg;
    double beta = atan2(b, a) * rad2deg;
    double chi = 90.0;

    printf("%.6f %.6f %.6f %.6f\n", c, alpha, beta, chi);
    return 0;
}
