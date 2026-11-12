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
    Лабораторная работа №1<br>
    <span style="font-weight: normal; text-transform: none;">по дисциплине: «Программирование на языке С»</span>
  </div>

  <div class="gost-center space-tema">
    на тему: <span class="gost-bold">«Программирование линейных вычислительных процессов»</span><br>
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

## Лабораторная работа 1

Вариант **19**. Факультет математики и компьютерных наук, Фундаментальная математика и механика.


### Задача №1

**Условие.** Даны катеты прямоугольного треугольника A и B. Найти гипотенузу C и углы треугольника α, β, χ (в градусах).


По теореме Пифагора гипотенуза \(C = \sqrt{A^2 + B^2}\) (функция `hypot`). Углы при катетах вычисляются через `atan2` в градусах; угол между катетами в прямоугольном треугольнике равен 90°.

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

    double a, b;

    printf("Введите катет A: ");
    fflush(stdout);
    if (scanf("%lf", &a) != 1) {
        return 1;
    }

    printf("Введите катет B: ");
    fflush(stdout);
    if (scanf("%lf", &b) != 1) {
        return 1;
    }

    double c = hypot(a, b);
    const double rad2deg = 180.0 / acos(-1.0);
    double alpha = atan2(a, b) * rad2deg;
    double beta = atan2(b, a) * rad2deg;
    double chi = 90.0;

    printf("C = %.6f, углы (град): %.6f %.6f %.6f\n", c, alpha, beta, chi);
    return 0;
}
```

**Ввод:**

```
3
4
```

**Вывод:**

```
Введите катет A: Введите катет B: C = 5.000000, углы (град): 36.869898 53.130102 90.000000
```
