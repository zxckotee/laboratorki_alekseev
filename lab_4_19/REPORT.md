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

**Условие.** Вычислить значение функции варианта 19 через отдельную функцию f(x): ln|cos(x − 2π)| − 9/√(1 − e^x)/(sin x − 3 − ⁵√x) для введённого x.


Значение вычисляется в функции `znachenie_f`: числитель берётся из логарифма модуля косинуса, знаменатель — из синуса, корня пятой степени и экспоненты. При недопустимом x программа сообщает об этом вместо числа.

**Код (`task_01.c`):**

```c
#include <math.h>
#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#endif

double znachenie_f(double x) {
    double nom = log(fabs(cos(x - 2.0 * acos(-1.0))));
    double znam = sin(x) - 3.0 - pow(x, 0.2);
    if (znam == 0.0) {
        return 0.0 / 0.0;
    }
    double drob = 9.0 / sqrt(fabs(1.0 - exp(x))) / znam;
    return nom - drob;
}

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif

    double x;

    printf("Введите x: ");
    fflush(stdout);
    if (scanf("%lf", &x) != 1) {
        return 1;
    }

    double y = znachenie_f(x);
    if (y != y) {
        printf("Значение функции не определено при данном x.\n");
        return 0;
    }

    printf("f(x) = %.6f\n", y);
    return 0;
}
```

**Ввод:**

```
0.5
```

**Вывод:**

```
Введите x: f(x) = 3.164524
```
