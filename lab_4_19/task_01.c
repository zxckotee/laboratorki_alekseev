#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#endif

double srednee_cifr(int chislo) {
    int modul;
    int summa;
    int kolichestvo;
    int ostatok;

    if (chislo == 0) {
        return 0.0;
    }

    modul = chislo;
    if (modul < 0) {
        modul = -modul;
    }

    summa = 0;
    kolichestvo = 0;
    while (modul > 0) {
        ostatok = modul % 10;
        summa = summa + ostatok;
        kolichestvo = kolichestvo + 1;
        modul = modul / 10;
    }

    return (double)summa / (double)kolichestvo;
}

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif

    int n;
    int i;
    int element;

    printf("Введите N: ");
    fflush(stdout);
    if (scanf("%d", &n) != 1 || n < 1) {
        return 1;
    }

    for (i = 0; i < n; ++i) {
        printf("Введите элемент последовательности: ");
        fflush(stdout);
        if (scanf("%d", &element) != 1) {
            return 1;
        }
        printf("Среднее цифр: %.6f\n", srednee_cifr(element));
    }

    return 0;
}