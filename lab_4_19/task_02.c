#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#endif

long long chislo_iz_sistemy(const char *zapis, int osnovanie) {
    int i;
    long long znachenie;
    int cifra;

    znachenie = 0;
    for (i = 0; zapis[i] != '\0'; ++i) {
        if (zapis[i] >= '0' && zapis[i] <= '9') {
            cifra = zapis[i] - '0';
        } else if (zapis[i] >= 'A' && zapis[i] <= 'Z') {
            cifra = zapis[i] - 'A' + 10;
        } else if (zapis[i] >= 'a' && zapis[i] <= 'z') {
            cifra = zapis[i] - 'a' + 10;
        } else {
            return -1;
        }
        if (cifra < 0 || cifra >= osnovanie) {
            return -1;
        }
        znachenie = znachenie * osnovanie + cifra;
    }
    return znachenie;
}

long long vychislit_C(long long A, long long B) {
    return B * B * B - 2 * B + A;
}

void vyvesti_v_sisteme(long long chislo, int osnovanie) {
    char cifry[70];
    int kolichestvo;
    long long ost;

    if (chislo == 0) {
        printf("0");
        return;
    }

    kolichestvo = 0;
    while (chislo > 0) {
        ost = chislo % osnovanie;
        if (ost < 10) {
            cifry[kolichestvo] = (char)('0' + ost);
        } else {
            cifry[kolichestvo] = (char)('A' + (ost - 10));
        }
        kolichestvo = kolichestvo + 1;
        chislo = chislo / osnovanie;
    }

    while (kolichestvo > 0) {
        kolichestvo = kolichestvo - 1;
        printf("%c", cifry[kolichestvo]);
    }
}

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif

    char zapis_A[70];
    char zapis_B[70];
    long long A;
    long long B;
    long long C;
    int p;
    int q;
    int r;

    p = 2;
    q = 4;
    r = 3;

    printf("Введите число A (основание %d): ", p);
    fflush(stdout);
    if (scanf("%69s", zapis_A) != 1) {
        return 1;
    }

    printf("Введите число B (основание %d): ", q);
    fflush(stdout);
    if (scanf("%69s", zapis_B) != 1) {
        return 1;
    }

    A = chislo_iz_sistemy(zapis_A, p);
    B = chislo_iz_sistemy(zapis_B, q);
    if (A < 0 || B < 0) {
        printf("Неверная запись числа.\n");
        return 1;
    }

    C = vychislit_C(A, B);

    printf("C в десятичной системе: %lld\n", C);
    printf("C в системе с основанием %d: ", r);
    vyvesti_v_sisteme(C, r);
    printf("\n");

    return 0;
}