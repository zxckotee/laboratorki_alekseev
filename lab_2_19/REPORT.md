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
    Лабораторная работа №2<br>
    <span style="font-weight: normal; text-transform: none;">по дисциплине: «Программирование на языке С»</span>
  </div>

  <div class="gost-center space-tema">
    на тему: <span class="gost-bold">«Программирование разветвляющихся процессов»</span><br>
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

## Лабораторная работа 2

Вариант **19**. Факультет математики и компьютерных наук, Фундаментальная математика и механика.


### Задача №1

**Условие.** Даны коэффициенты двух прямых y = a1·x + b1 и y = a2·x + b2. Определить, совпадают ли прямые, параллельны ли или пересекаются; при пересечении найти координаты точки.


Две прямые y = a1·x + b1 и y = a2·x + b2. Если коэффициенты при x и свободные члены совпадают — прямые совпадают; если только k совпадает — параллельны; иначе считаем точку пересечения.

**Код (`task_01.c`):**

```c
#include <math.h>
#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#endif

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif

    double a1, b1, a2, b2;

    printf("Введите a1: ");
    fflush(stdout);
    if (scanf("%lf", &a1) != 1) {
        return 1;
    }
    printf("Введите b1: ");
    fflush(stdout);
    if (scanf("%lf", &b1) != 1) {
        return 1;
    }
    printf("Введите a2: ");
    fflush(stdout);
    if (scanf("%lf", &a2) != 1) {
        return 1;
    }
    printf("Введите b2: ");
    fflush(stdout);
    if (scanf("%lf", &b2) != 1) {
        return 1;
    }

    if (fabs(a1 - a2) < 1e-9 && fabs(b1 - b2) < 1e-9) {
        printf("Прямые совпадают.\n");
    } else if (fabs(a1 - a2) < 1e-9) {
        printf("Прямые параллельны (не совпадают).\n");
    } else {
        printf("Прямые пересекаются.\n");
        double x = (b2 - b1) / (a1 - a2);
        double y = a1 * x + b1;
        printf("Точка пересечения: x = %.6f, y = %.6f\n", x, y);
    }

    return 0;
}
```

**Ввод:**

```
1
2
2
5
```

**Вывод:**

```
Введите a1: Введите b1: Введите a2: Введите b2: Прямые пересекаются.
Точка пересечения: x = -3.000000, y = -1.000000
```
