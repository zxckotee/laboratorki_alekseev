#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#endif

int prostoe(int x) {
    int d;

    if (x < 2) {
        return 0;
    }
    if (x == 2) {
        return 1;
    }
    if (x % 2 == 0) {
        return 0;
    }
    for (d = 3; d * d <= x; d += 2) {
        if (x % d == 0) {
            return 0;
        }
    }
    return 1;
}

int cifry_ubyvayut(int x) {
    int stepen;
    int pred;
    int c;

    if (x < 0) {
        return 0;
    }
    if (x == 0) {
        return 0;
    }

    stepen = 1;
    while (x >= stepen * 10) {
        stepen *= 10;
    }

    pred = -1;
    while (stepen > 0) {
        c = x / stepen;
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

int naiti_min_dlina(FILE *f) {
    int x;
    int dlina;
    int min_dlina;

    min_dlina = 0;
    dlina = 0;

    rewind(f);
    while (fscanf(f, "%d", &x) == 1) {
        if (podhodit(x)) {
            dlina++;
        } else if (dlina > 0) {
            if (min_dlina == 0 || dlina < min_dlina) {
                min_dlina = dlina;
            }
            dlina = 0;
        }
    }
    if (dlina > 0) {
        if (min_dlina == 0 || dlina < min_dlina) {
            min_dlina = dlina;
        }
    }

    return min_dlina;
}

int naiti_nomer_gruppy(FILE *f, int nuzh_dlina) {
    int x;
    int dlina;
    int nomer;

    nomer = 0;
    dlina = 0;

    rewind(f);
    while (fscanf(f, "%d", &x) == 1) {
        if (podhodit(x)) {
            dlina++;
        } else if (dlina > 0) {
            nomer++;
            if (dlina == nuzh_dlina) {
                return nomer;
            }
            dlina = 0;
        }
    }
    if (dlina > 0) {
        nomer++;
        if (dlina == nuzh_dlina) {
            return nomer;
        }
    }

    return 0;
}

void vyvesti_gruppu(FILE *f, int nomer_gruppy) {
    int x;
    int zakoncheno;
    int v_gruppe;
    int pechat;
    int pervaya;

    zakoncheno = 0;
    v_gruppe = 0;
    pechat = 0;
    pervaya = 1;

    rewind(f);
    while (fscanf(f, "%d", &x) == 1) {
        if (podhodit(x)) {
            if (!v_gruppe) {
                v_gruppe = 1;
                pechat = (zakoncheno + 1 == nomer_gruppy);
            }
            if (pechat) {
                if (!pervaya) {
                    printf(" ");
                }
                printf("%d", x);
                pervaya = 0;
            }
        } else if (v_gruppe) {
            zakoncheno++;
            v_gruppe = 0;
            pechat = 0;
            if (zakoncheno == nomer_gruppy) {
                return;
            }
        }
    }
    if (v_gruppe) {
        zakoncheno++;
        (void)zakoncheno;
    }
}

int main(void) {
    FILE *f;
    int x;
    int min_dlina;
    int nomer;

#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif

    f = tmpfile();
    if (f == NULL) {
        return 1;
    }

    printf("Вводите целые числа (0 — конец последовательности):\n");

    for (;;) {
        printf("Введите число: ");
        fflush(stdout);
        if (scanf("%d", &x) != 1) {
            fclose(f);
            return 1;
        }
        if (x == 0) {
            break;
        }
        fprintf(f, "%d ", x);
    }

    min_dlina = naiti_min_dlina(f);
    if (min_dlina == 0) {
        printf("Подходящая группа не найдена.\n");
        fclose(f);
        return 0;
    }

    nomer = naiti_nomer_gruppy(f, min_dlina);
    if (nomer == 0) {
        printf("Подходящая группа не найдена.\n");
        fclose(f);
        return 0;
    }

    printf("Минимальная длина группы: %d\n", min_dlina);
    printf("Группа: ");
    vyvesti_gruppu(f, nomer);
    printf("\n");

    fclose(f);
    return 0;
}