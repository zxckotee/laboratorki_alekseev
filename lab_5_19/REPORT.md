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
    Лабораторная работа №5<br>
    <span style="font-weight: normal; text-transform: none;">по дисциплине: «Программирование на языке С»</span>
  </div>

  <div class="gost-center space-tema">
    на тему: <span class="gost-bold">«Работа с группами чисел в последовательности»</span><br>
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

## Лабораторная работа 5

Вариант **19**. Факультет математики и компьютерных наук, Фундаментальная математика и механика.


### Задача №1

**Условие.** Вводится последовательность целых чисел (0 — конец), найти группу минимальной длины из простых чисел, цифры которых образуют убывающую последовательность.


Последовательность читается до нуля. Группа — подряд идущие простые числа, цифры которых строго убывают слева направо. Среди таких групп выбирается группа минимальной длины.

Подробный разбор синтаксиса и логики (список `Node`, указатели): см. `task_01_commented.c`.

**Код (`task_01.c`):**

```c
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
```

**Ввод:**

```
953
0
```

**Вывод:**

```
Вводите целые числа (0 — конец последовательности):
Введите число: Введите число: Минимальная длина группы: 1
Группа: 953
```
