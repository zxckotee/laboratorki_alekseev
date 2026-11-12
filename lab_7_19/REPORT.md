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
    Лабораторная работа №7<br>
    <span style="font-weight: normal; text-transform: none;">по дисциплине: «Программирование на языке С»</span>
  </div>

  <div class="gost-center space-tema">
    на тему: <span class="gost-bold">«Использование указателей в функциях»</span><br>
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

## Лабораторная работа 7

Вариант **19**. Факультет математики и компьютерных наук, Фундаментальная математика и механика.


### Задача №1

**Условие.** Функция решения квадратного уравнения. Задано N парабол y = ax² + bx + c. Вычислить среднее арифметическое абсцисс точек пересечения всех парабол с осью OX.


Корни квадратного уравнения возвращаются через указатели в `solve_quadratic`. Для N парабол накапливается сумма всех действительных корней уравнений `y = 0` и выводится среднее.

**Код (`task_01.c`):**

```c
#include <math.h>
#include <stdio.h>

static int solve_quadratic(double a, double b, double c, double *r1, double *r2) {
    if (fabs(a) < 1e-12) {
        return 0;
    }
    double d = b * b - 4.0 * a * c;
    if (d < 0.0) {
        return 0;
    }
    if (d == 0.0) {
        *r1 = -b / (2.0 * a);
        return 1;
    }
    double sd = sqrt(d);
    *r1 = (-b - sd) / (2.0 * a);
    *r2 = (-b + sd) / (2.0 * a);
    return 2;
}

int main(void) {
    int n;
    printf("Введите количество парабол N: ");
    fflush(stdout);
    if (scanf("%d", &n) != 1 || n < 1) {
        return 1;
    }

    double sum = 0.0;
    int root_count = 0;

    for (int i = 1; i <= n; ++i) {
        double a, b, c;
        printf("Введите коэффициент a для параболы %d: ", i);
        fflush(stdout);
        if (scanf("%lf", &a) != 1) {
            return 1;
        }
        printf("Введите коэффициент b для параболы %d: ", i);
        fflush(stdout);
        if (scanf("%lf", &b) != 1) {
            return 1;
        }
        printf("Введите коэффициент c для параболы %d: ", i);
        fflush(stdout);
        if (scanf("%lf", &c) != 1) {
            return 1;
        }

        double x1 = 0.0;
        double x2 = 0.0;
        int k = solve_quadratic(a, b, c, &x1, &x2);
        if (k >= 1) {
            sum += x1;
            ++root_count;
        }
        if (k == 2) {
            sum += x2;
            ++root_count;
        }
    }

    if (root_count == 0) {
        printf("Действительных точек пересечения с осью OX нет.\n");
        return 0;
    }

    printf("Среднее арифметическое абсцисс: %.6f\n", sum / (double)root_count);
    return 0;
}
```

**Ввод:**

```
2
1
0
-4
1
0
-1
```

**Вывод:**

```
Введите количество парабол N: Введите коэффициент a для параболы 1: Введите коэффициент b для параболы 1: Введите коэффициент c для параболы 1: Введите коэффициент a для параболы 2: Введите коэффициент b для параболы 2: Введите коэффициент c для параболы 2: Среднее арифметическое абсцисс: 0.000000
```
