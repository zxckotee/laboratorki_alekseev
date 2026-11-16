#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#endif

int prostoe(int x) {
    if (x < 2) {
        return 0;
    }
    if (x == 2) {
        return 1;
    }
    if (x % 2 == 0) {
        return 0;
    }
    for (int d = 3; d * d <= x; d += 2) {
        if (x % d == 0) {
            return 0;
        }
    }
    return 1;
}

int cifry_ubyvayut(int x) {
    if (x < 0) {
        return 0;
    }
    int stepen = 1;
    while (x >= stepen * 10) {
        stepen *= 10;
    }
    int pred = -1;
    while (stepen > 0) {
        int c = x / stepen;
        c %= 10;
        if (pred >= 0 && c >= pred) {
            return 0;
        }
        pred = c;
        stepen /= 10;
    }
    return 1;
}

int podhodit(int x) {
    return prostoe(x) && cifry_ubyvayut(x);
}

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif

    int x;
    int tek[500];
    int tek_dlina = 0;
    int luch[500];
    int luch_dlina = 0;

    printf("Вводите целые числа (0 — конец последовательности):\n");

    for (;;) {
        printf("Введите число: ");
        fflush(stdout);
        if (scanf("%d", &x) != 1) {
            return 1;
        }
        if (x == 0) {
            if (tek_dlina > 0 && (luch_dlina == 0 || tek_dlina < luch_dlina)) {
                luch_dlina = tek_dlina;
                for (int i = 0; i < tek_dlina; ++i) {
                    luch[i] = tek[i];
                }
            }
            break;
        }

        if (podhodit(x)) {
            if (tek_dlina < 500) {
                tek[tek_dlina++] = x;
            }
        } else {
            if (tek_dlina > 0 && (luch_dlina == 0 || tek_dlina < luch_dlina)) {
                luch_dlina = tek_dlina;
                for (int i = 0; i < tek_dlina; ++i) {
                    luch[i] = tek[i];
                }
            }
            tek_dlina = 0;
        }
    }

    if (luch_dlina == 0) {
        printf("Подходящая группа не найдена.\n");
        return 0;
    }

    printf("Минимальная длина группы: %d\n", luch_dlina);
    printf("Группа: ");
    for (int i = 0; i < luch_dlina; ++i) {
        if (i > 0) {
            printf(" ");
        }
        printf("%d", luch[i]);
    }
    printf("\n");
    return 0;
}