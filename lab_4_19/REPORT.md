<style>
  @media print {
    @page {
      size: A4;
      margin: 20mm 15mm 20mm 20mm;
    }
    .gost-page-break {
      page-break-after: always !important;
      break-after: page !important;
    }
  }
  body, html {
    margin: 0;
    padding: 0;
    font-family: "Times New Roman", Times, serif;
    font-size: 14pt;
    line-height: 1.5;
    color: #000;
  }
  .gost-center { text-align: center; }
  .gost-bold { font-weight: bold; }
  .gost-uppercase { text-transform: uppercase; }
  .space-vedomstvo { margin-bottom: 20mm; }
  .space-kafedra { margin-bottom: 30mm; }
  .space-tema { margin-bottom: 35mm; }
  .gost-signatures-block {
    margin-left: 105mm;
    text-align: left;
    line-height: 1.7;
  }
  .gost-footer-city { margin-top: 45mm; }
</style>

<div class="gost-page-break">

  <div class="gost-center gost-uppercase space-vedomstvo">
    Министерство науки и высшего образования <br>Российской Федерации<br>
    Федеральное государственное бюджетное образовательное<br> учреждение
    высшего образования<br>
    <span class="gost-bold">«КУБАНСКИЙ ГОСУДАРСТВЕННЫЙ УНИВЕРСИТЕТ»</span>
  </div>

  <div class="gost-center space-kafedra">
    Кафедра информационных образовательных технологий
  </div>

  <div class="gost-center gost-uppercase gost-bold" style="margin-bottom: 15mm;">
    Лабораторная работа №4<br>
    <span style="font-weight: normal; text-transform: none;">по дисциплине: «Программирование на языке С»</span>
  </div>

  <div class="gost-center space-tema">
    на тему: <span class="gost-bold">«Применение функций»</span><br>
    <span style="font-weight: normal;">Вариант 19</span>
  </div>

  <div class="gost-signatures-block">
    <strong>Выполнил:</strong><br>
    Студент группы 14-А<br>
    ___________ / М. А. Черниенко<br>
    «___» _________ 2026 г.<br><br>
    <strong>Проверил:</strong><br>
    Доцент, к.т.н.<br>
    ___________ / Е. Р. Алексеев<br>
    «___» _________ 2026 г.
  </div>

  <div class="gost-center gost-footer-city">
    Краснодар, 2026
  </div>

</div>

<!-- -->

## Лабораторная работа 4

Вариант **19**. Факультет математики и компьютерных наук, Фундаментальная математика и механика.


### Задача №1

**Условие.** Вводится последовательность из N целых элементов. Для каждого элемента последовательности найти среднее значение его цифр.


Сначала вводится N, затем N целых чисел. Функция `srednee_cifr` берёт модуль числа, в цикле складывает цифры и делит сумму на их количество; для нуля среднее равно 0. В `main` для каждого элемента выводится полученное среднее.

**Код (`task_01.c`):**

```c
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
```

**Ввод:**

```
3
123
-45
0
```

**Вывод:**

```
Введите N: Введите элемент последовательности: Среднее цифр: 2.000000
Введите элемент последовательности: Среднее цифр: 4.500000
Введите элемент последовательности: Среднее цифр: 0.000000
```


### Задача №2

**Условие.** Заданы A и B в системах счисления с основаниями p=2 и q=4. Вычислить C = B³ − 2·B + A и вывести C в десятичной системе и в системе с основанием r=3. Использовать функции.


Числа A и B читаются как строки в двоичной и четверичной системах. Функция `chislo_iz_sistemy` переводит запись в десятичное значение, `vychislit_C` считает B³ − 2B + A. Результат печатается в десятичном виде и функцией `vyvesti_v_sisteme` — в троичной системе (r = 3).

**Код (`task_02.c`):**

```c
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
```

**Ввод:**

```
101
20
```

**Вывод:**

```
Введите число A (основание 2): Введите число B (основание 4): C в десятичной системе: 501
C в системе с основанием 3: 200120
```
