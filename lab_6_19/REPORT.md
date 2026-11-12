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
    Лабораторная работа №6<br>
    <span style="font-weight: normal; text-transform: none;">по дисциплине: «Программирование на языке С»</span>
  </div>

  <div class="gost-center space-tema">
    на тему: <span class="gost-bold">«Программирование циклических алгоритмов»</span><br>
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

## Лабораторная работа 6

Вариант **19**. Факультет математики и компьютерных наук, Фундаментальная математика и механика.


### Задача №1

**Условие.** Вывести на экран первые n совершенных чисел, их сумму и среднее значение.


Совершенные числа находятся перебором; сумма собственных делителей сравнивается с числом. Выводятся первые n совершенных, их сумма и среднее арифметическое.

**Код (`task_01.c`):**

```c
#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#endif


static int is_perfect(int x) {
    if (x < 2) {
        return 0;
    }
    int sum = 1;
    for (int d = 2; d * d <= x; ++d) {
        if (x % d == 0) {
            sum += d;
            if (d != x / d) {
                sum += x / d;
            }
        }
    }
    return sum == x;
}

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif

    int n;
    printf("Введите количество совершенных чисел n: ");
    fflush(stdout);
    if (scanf("%d", &n) != 1 || n < 1) {
        return 1;
    }

    long long sum = 0;
    int found = 0;
    for (int x = 2; found < n; ++x) {
        if (is_perfect(x)) {
            printf("%d\n", x);
            sum += x;
            ++found;
        }
    }

    printf("Сумма: %lld\n", sum);
    printf("Среднее: %.6f\n", (double)sum / (double)n);
    return 0;
}
```

**Ввод:**

```
2
```

**Вывод:**

```
Введите количество совершенных чисел n: 6
28
Сумма: 34
Среднее: 17.000000
```


### Задача №2

**Условие.** Вводится последовательность целых чисел до n-го избыточного числа. Найти второе по величине число в последовательности.


Избыточное число: сумма собственных делителей больше самого числа. Ввод идёт до n-го избыточного; второй максимум обновляется за один проход.

**Код (`task_02.c`):**

```c
#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#endif


static int sum_proper_divisors(int x) {
    if (x < 2) {
        return 0;
    }
    int sum = 1;
    for (int d = 2; d * d <= x; ++d) {
        if (x % d == 0) {
            sum += d;
            if (d != x / d) {
                sum += x / d;
            }
        }
    }
    return sum;
}

static int is_abundant(int x) {
    return x > 1 && sum_proper_divisors(x) > x;
}

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif

    int need;
    printf("Введите номер избыточного числа n: ");
    fflush(stdout);
    if (scanf("%d", &need) != 1 || need < 1) {
        return 1;
    }

    int abundant = 0;
    int max1 = 0;
    int max2 = 0;
    int count = 0;

    while (abundant < need) {
        int x;
        printf("Введите целое число: ");
        fflush(stdout);
        if (scanf("%d", &x) != 1) {
            return 1;
        }
        ++count;
        if (x > max1) {
            max2 = max1;
            max1 = x;
        } else if (x > max2) {
            max2 = x;
        }
        if (is_abundant(x)) {
            ++abundant;
        }
    }

    if (count < 2) {
        printf("Недостаточно чисел для второго максимума.\n");
        return 0;
    }

    printf("Второе по величине число: %d\n", max2);
    return 0;
}
```

**Ввод:**

```
2
10
12
15
18
```

**Вывод:**

```
Введите номер избыточного числа n: Введите целое число: Введите целое число: Введите целое число: Введите целое число: Второе по величине число: 15
```


### Задача №3

**Условие.** Найти произведение первых n чисел Армстронга (программа должна работать при n=14).


Число Армстронга: сумма цифр в степени их количества равна числу. Произведение первых n таких чисел считается в типе long double.

**Код (`task_03.c`):**

```c
#include <math.h>
#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#endif


static int digit_count(int x) {
    int n = 0;
    if (x == 0) {
        return 1;
    }
    while (x > 0) {
        ++n;
        x /= 10;
    }
    return n;
}

static int is_armstrong(int x) {
    if (x < 0) {
        return 0;
    }
    int k = digit_count(x);
    int t = x;
    long long sum = 0;
    while (t > 0) {
        int d = t % 10;
        sum += (long long)pow(d, k);
        t /= 10;
    }
    return sum == x;
}

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif

    int n;
    printf("Введите n: ");
    fflush(stdout);
    if (scanf("%d", &n) != 1 || n < 1) {
        return 1;
    }

    long double product = 1.0L;
    int found = 0;
    for (int x = 1; found < n; ++x) {
        if (is_armstrong(x)) {
            product *= (long double)x;
            ++found;
        }
    }

    printf("Произведение: %.6f\n", (double)product);
    return 0;
}
```

**Ввод:**

```
4
```

**Вывод:**

```
Введите n: Произведение: 24.000000
```


### Задача №4

**Условие.** Вычислить S(x) и Y(x) = (x−1)·e^(x/2) на [0, 1] с шагом h, n слагаемых с клавиатуры. Таблица x, S(x), Y(x).


Ряд S(x) с членами (2k−1)x^k/(2^k k!) прибавляется к −1; Y(x) = (x−1)e^(x/2). Таблица на [0, 1] с шагом h.

**Код (`task_04.c`):**

```c
#include <math.h>
#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#endif


static double series_s(double x, int n) {
    double s = -1.0;
    for (int k = 1; k <= n; ++k) {
        long long fact = 1;
        for (int i = 2; i <= k; ++i) {
            fact *= i;
        }
        double term = (2.0 * k - 1.0) * pow(x, k) / (pow(2.0, k) * (double)fact);
        s += term;
    }
    return s;
}

static double y_func(double x) {
    return (x - 1.0) * exp(x / 2.0);
}

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif

    int n;
    double h;
    printf("Введите количество слагаемых n: ");
    fflush(stdout);
    if (scanf("%d", &n) != 1 || n < 1) {
        return 1;
    }
    printf("Введите шаг h: ");
    fflush(stdout);
    if (scanf("%lf", &h) != 1 || h <= 0.0) {
        return 1;
    }

    printf("x\tS(x)\t\tY(x)\n");
    for (double x = 0.0; x <= 1.0 + 1e-9; x += h) {
        if (x > 1.0) {
            x = 1.0;
        }
        printf("%.4f\t%.6f\t%.6f\n", x, series_s(x, n), y_func(x));
        if (fabs(x - 1.0) < 1e-9) {
            break;
        }
    }
    return 0;
}
```

**Ввод:**

```
5
0.25
```

**Вывод:**

```
Введите количество слагаемых n: Введите шаг h: x	S(x)		Y(x)
0.0000	-1.000000	-1.000000
0.2500	-0.849861	-0.849861
0.5000	-0.642017	-0.642013
0.7500	-0.363793	-0.363748
1.0000	-0.000260	0.000000
```


### Задача №5

**Условие.** y = −x²/3 + x⁴/5 + … + (−1)^n · x^(2n)/(2n+1); n и x с клавиатуры.


Сумма знакочередующихся слагаемых (−1)^k · x^(2k)/(2k+1) при k от 1 до n.

**Код (`task_05.c`):**

```c
#include <math.h>
#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#endif


static double compute_y(double x, int n) {
    double y = 0.0;
    for (int k = 1; k <= n; ++k) {
        double sign = (k % 2 == 1) ? -1.0 : 1.0;
        y += sign * pow(x, 2.0 * k) / (2.0 * k + 1.0);
    }
    return y;
}

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif

    int n;
    double x;
    printf("Введите натуральное n: ");
    fflush(stdout);
    if (scanf("%d", &n) != 1 || n < 1) {
        return 1;
    }
    printf("Введите x: ");
    fflush(stdout);
    if (scanf("%lf", &x) != 1) {
        return 1;
    }

    printf("y = %.6f\n", compute_y(x, n));
    return 0;
}
```

**Ввод:**

```
3
0.5
```

**Вывод:**

```
Введите натуральное n: Введите x: y = -0.073065
```
