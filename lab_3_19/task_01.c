#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#endif

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif

    long long l;

    printf("Введите расстояние L в метрах: ");
    fflush(stdout);
    if (scanf("%lld", &l) != 1 || l < 0) {
        return 1;
    }

    long long km = l / 1000;
    long long ost = l % 1000;

    printf("Полных километров: %lld\n", km);
    printf("Остаток в метрах: %lld\n", ost);

    return 0;
}