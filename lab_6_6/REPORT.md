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
    <span style="font-weight: normal;">Вариант 6</span>
  </div>

  <div class="gost-signatures-block">
    <strong>Выполнил:</strong><br>
    Студент группы 14-А<br>
    ___________ / И. Р. Аблязов<br>
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

Вариант **6**. Факультет математики и компьютерных наук, Фундаментальная математика и механика.


### Задача №1

**Условие.** Вывести на экран первые n простых чисел в диапазоне a до b.


Простота проверяется перебором делителей до √x. Цикл по диапазону [a, b] накапливает ровно n первых простых чисел и печатает их в одной строке.

**Код (`task_01.c`):**

```c
#include <stdio.h>

static int is_prime(int x) {
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

int main(void) {
    int a, b, n;
    if (scanf("%d %d %d", &a, &b, &n) != 3 || n < 1 || a > b) {
        return 1;
    }

    int found = 0;
    for (int x = a; x <= b && found < n; ++x) {
        if (is_prime(x)) {
            if (found > 0) {
                printf(" ");
            }
            printf("%d", x);
            ++found;
        }
    }
    printf("\n");
    return found == n ? 0 : 0;
}
```

**Ввод:**

```
10 50 5
```

**Вывод:**

```
11 13 17 19 23
```


### Задача №2

**Условие.** Вводится последовательность целых чисел, которая заканчивается после ввода n чисел-палиндромов. Введенные числа вывести в восьмеричной системе счисления.


Палиндром проверяется сравнением числа с его переворотом. В цикле читаем числа, печатаем каждое в восьмеричном виде (`%o`), выходим, когда среди введённых набралось n палиндромов.

**Код (`task_02.c`):**

```c
#include <stdio.h>

static int is_palindrome(int x) {
    if (x < 0) {
        return 0;
    }
    int orig = x;
    int rev = 0;
    if (x == 0) {
        return 1;
    }
    while (x > 0) {
        rev = rev * 10 + x % 10;
        x /= 10;
    }
    return orig == rev;
}

int main(void) {
    int need;
    if (scanf("%d", &need) != 1 || need < 1) {
        return 1;
    }

    int pal_count = 0;
    int value;
    int first = 1;
    while (pal_count < need && scanf("%d", &value) == 1) {
        if (!first) {
            printf(" ");
        }
        printf("%o", value);
        first = 0;
        if (is_palindrome(value)) {
            ++pal_count;
        }
    }
    printf("\n");
    return pal_count == need ? 0 : 1;
}
```

**Ввод:**

```
2
10 121 7
```

**Вывод:**

```
12 171 7
```


### Задача №3

**Условие.** Найти корень квадратный из суммы первых n (100 ≤ n ≤ 1000) чисел-палиндромов.


Натуральные палиндромы перебираются по возрастанию; накапливается сумма первых n штук. Результат — квадратный корень из этой суммы (`sqrt`).

**Код (`task_03.c`):**

```c
#include <math.h>
#include <stdio.h>

static int is_palindrome(int x) {
    if (x < 0) {
        return 0;
    }
    int orig = x;
    int rev = 0;
    int t = x;
    while (t > 0) {
        rev = rev * 10 + t % 10;
        t /= 10;
    }
    if (x == 0) {
        return 1;
    }
    return orig == rev;
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1 || n < 100 || n > 1000) {
        return 1;
    }

    long long sum = 0;
    int count = 0;
    for (int x = 1; count < n; ++x) {
        if (is_palindrome(x)) {
            sum += x;
            ++count;
        }
    }

    printf("%.6f\n", sqrt((double)sum));
    return 0;
}
```

**Ввод:**

```
100
```

**Вывод:**

```
205.737697
```


### Задача №4

**Условие.** Составьте программу вычисления суммы S(x) = x + x³/3! + … + x^(2n−1)/(2n−1)! и функции Y(x) = (e^x − e^(−x))/2 в диапазоне от 0 до 1 с шагом h. Значение n вводится с клавиатуры. Вывести таблицу x, S(x), Y(x).


Y(x) — гиперболический синус `sinh(x)`. Члены ряда S(x) соответствуют нечётным степеням x с факториалами в знаменателе; с шагом h печатается таблица для x ∈ [0, 1].

**Код (`task_04.c`):**

```c
#include <math.h>
#include <stdio.h>

static double sinh_ref(double x) {
    return (exp(x) - exp(-x)) / 2.0;
}

static double series_sinh(double x, int n) {
    double s = 0.0;
    for (int k = 1; k <= n; ++k) {
        int power = 2 * k - 1;
        double term = pow(x, power);
        long long fact = 1;
        for (int f = 2; f <= power; ++f) {
            fact *= f;
        }
        s += term / (double)fact;
    }
    return s;
}

int main(void) {
    int n;
    double h;
    if (scanf("%d %lf", &n, &h) != 2 || n < 1 || h <= 0.0) {
        return 1;
    }

    printf("x\tS(x)\t\tY(x)\n");
    for (double x = 0.0; x <= 1.0 + 1e-9; x += h) {
        if (x > 1.0) {
            x = 1.0;
        }
        printf("%.4f\t%.6f\t%.6f\n", x, series_sinh(x, n), sinh_ref(x));
        if (fabs(x - 1.0) < 1e-9) {
            break;
        }
    }
    return 0;
}
```

**Ввод:**

```
6 0.25
```

**Вывод:**

```
x	S(x)		Y(x)
0.0000	0.000000	0.000000
0.2500	0.252612	0.252612
0.5000	0.521095	0.521095
0.7500	0.822317	0.822317
1.0000	1.175201	1.175201
```


### Задача №5

**Условие.** Напишите программу для вычисления y по формуле: y = −x²/(1·2) + x³/(2·4) − x⁴/(3·8) + … + (−1)^n · x^(n+1)/(n·2^n). Натуральное n и x (|x| < 1) вводятся с клавиатуры.


Каждое слагаемое имеет вид (−1)^k · x^(k+1) / (k · 2^k) при k = 1…n. Цикл суммирует члены; для степеней и знаменателя используются `pow`.

**Код (`task_05.c`):**

```c
#include <math.h>
#include <stdio.h>

static double compute_y(double x, int n) {
    double y = 0.0;
    for (int k = 1; k <= n; ++k) {
        double sign = (k % 2 == 1) ? -1.0 : 1.0;
        double denom = (double)k * pow(2.0, k);
        double xp = pow(x, k + 1);
        y += sign * xp / denom;
    }
    return y;
}

int main(void) {
    int n;
    double x;
    if (scanf("%d %lf", &n, &x) != 2 || n < 1 || fabs(x) >= 1.0) {
        return 1;
    }

    printf("%.6f\n", compute_y(x, n));
    return 0;
}
```

**Ввод:**

```
4 0.5
```

**Вывод:**

```
-0.111491
```
