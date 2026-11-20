#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#endif

int simvol_v_cifru(char simvol, int osnovanie) {
    int cifra;

    if (simvol >= '0' && simvol <= '9') {
        cifra = simvol - '0';
    } else if (simvol >= 'A' && simvol <= 'Z') {
        cifra = simvol - 'A' + 10;
    } else if (simvol >= 'a' && simvol <= 'z') {
        cifra = simvol - 'a' + 10;
    } else {
        return -1;
    }

    if (cifra < 0 || cifra >= osnovanie) {
        return -1;
    }
    return cifra;
}

long long prochitat_chislo(int osnovanie) {
    long long znachenie;
    char simvol;
    int cifra;
    int est_cifra;

    znachenie = 0;
    est_cifra = 0;
    while (scanf("%c", &simvol) == 1) {
        if (simvol == '\n' || simvol == ' ' || simvol == '\t' || simvol == '\r') {
            if (est_cifra) {
                break;
            }
            continue;
        }
        cifra = simvol_v_cifru(simvol, osnovanie);
        if (cifra < 0) {
            return -1;
        }
        znachenie = znachenie * osnovanie + cifra;
        est_cifra = 1;
    }

    if (!est_cifra) {
        return -1;
    }
    return znachenie;
}

long long vychislit_C(long long A, long long B) {
    return B * B * B - 2 * B + A;
}

void vyvesti_cifru(long long ost) {
    if (ost < 10) {
        printf("%lld", ost);
    } else {
        printf("%c", (char)('A' + (ost - 10)));
    }
}

void vyvesti_v_sisteme(long long chislo, int osnovanie) {
    if (chislo == 0) {
        return;
    }
    vyvesti_v_sisteme(chislo / osnovanie, osnovanie);
    vyvesti_cifru(chislo % osnovanie);
}

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif

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
    A = prochitat_chislo(p);
    if (A < 0) {
        printf("Неверная запись числа.\n");
        return 1;
    }

    printf("Введите число B (основание %d): ", q);
    fflush(stdout);
    B = prochitat_chislo(q);
    if (B < 0) {
        printf("Неверная запись числа.\n");
        return 1;
    }

    C = vychislit_C(A, B);

    printf("C в десятичной системе: %lld\n", C);
    printf("C в системе с основанием %d: ", r);
    if (C == 0) {
        printf("0");
    } else {
        vyvesti_v_sisteme(C, r);
    }
    printf("\n");

    return 0;
}