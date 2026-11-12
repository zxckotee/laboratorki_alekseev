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
    Лабораторная работа №8<br>
    <span style="font-weight: normal; text-transform: none;">по дисциплине: «Программирование на языке С»</span>
  </div>

  <div class="gost-center space-tema">
    на тему: <span class="gost-bold">«Обработка массивов»</span><br>
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

## Лабораторная работа 8

Вариант **6**. Факультет математики и компьютерных наук, Фундаментальная математика и механика.


### Задача №1

**Условие.** Задан массив вещественных X(n): сумма положительных; произведение на нечётных индексах во 2-й половине; объединение с Y(m) в Z (отриц., нули, положит.); удаление максимума из Z.


Задача №1 варианта из методички: операции с массивами по условию в task_01.json.

**Код (`task_01.c`):**

```c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n, m;
    printf("Введите размер массива X (n): ");
    fflush(stdout);
    if (scanf("%d", &n) != 1 || n < 1) {
        return 1;
    }
    double *x = malloc((size_t)n * sizeof(double));
    if (!x) {
        return 1;
    }
    printf("Введите %d вещественных элементов X:\n", n);
    for (int i = 0; i < n; ++i) {
        printf("X[%d]: ", i + 1);
        fflush(stdout);
        if (scanf("%lf", &x[i]) != 1) {
            free(x);
            return 1;
        }
    }

    double sum_pos = 0.0;
    for (int i = 0; i < n; ++i) {
        if (x[i] > 0.0) {
            sum_pos += x[i];
        }
    }

    double prod = 1.0;
    int has = 0;
    int half = n / 2;
    for (int i = half; i < n; ++i) {
        if ((i + 1) % 2 == 1) {
            prod *= x[i];
            has = 1;
        }
    }
    if (!has) {
        prod = 0.0;
    }

    printf("Сумма положительных: %.6f\n", sum_pos);
    printf("Произведение (2-я половина, нечетный индекс): %.6f\n", prod);

    printf("Введите размер массива Y (m): ");
    fflush(stdout);
    if (scanf("%d", &m) != 1 || m < 1) {
        free(x);
        return 1;
    }
    double *y = malloc((size_t)m * sizeof(double));
    if (!y) {
        free(x);
        return 1;
    }
    printf("Введите %d вещественных элементов Y:\n", m);
    for (int i = 0; i < m; ++i) {
        printf("Y[%d]: ", i + 1);
        fflush(stdout);
        if (scanf("%lf", &y[i]) != 1) {
            free(x);
            free(y);
            return 1;
        }
    }

    int cap = n + m;
    double *neg = malloc((size_t)cap * sizeof(double));
    double *zer = malloc((size_t)cap * sizeof(double));
    double *pos = malloc((size_t)cap * sizeof(double));
    int cn = 0, cz = 0, cp = 0;

    for (int i = 0; i < n + m; ++i) {
        double v = (i < n) ? x[i] : y[i - n];
        if (v < 0.0) {
            neg[cn++] = v;
        } else if (v == 0.0) {
            zer[cz++] = v;
        } else {
            pos[cp++] = v;
        }
    }

    free(x);
    free(y);

    int zlen = cn + cz + cp;
    double *z = malloc((size_t)zlen * sizeof(double));
    int zi = 0;
    for (int i = 0; i < cn; ++i) {
        z[zi++] = neg[i];
    }
    for (int i = 0; i < cz; ++i) {
        z[zi++] = zer[i];
    }
    for (int i = 0; i < cp; ++i) {
        z[zi++] = pos[i];
    }

    int imax = 0;
    for (int i = 1; i < zlen; ++i) {
        if (z[i] > z[imax]) {
            imax = i;
        }
    }
    for (int i = imax; i < zlen - 1; ++i) {
        z[i] = z[i + 1];
    }
    --zlen;

    printf("Массив Z после удаления максимума (%d элементов): ", zlen);
    for (int i = 0; i < zlen; ++i) {
        if (i) {
            printf(" ");
        }
        printf("%.6f", z[i]);
    }
    printf("\n");

    free(neg);
    free(zer);
    free(pos);
    free(z);
    return 0;
}
```

**Ввод:**

```
4
1
-2
3
-1
2
0
5
```

**Вывод:**

```
Введите размер массива X (n): Введите 4 вещественных элементов X:
X[1]: X[2]: X[3]: X[4]: Сумма положительных: 4.000000
Произведение (2-я половина, нечетный индекс): 3.000000
Введите размер массива Y (m): Введите 2 вещественных элементов Y:
Y[1]: Y[2]: Массив Z после удаления максимума (5 элементов): -2.000000 -1.000000 0.000000 1.000000 3.000000
```


### Задача №2

**Условие.** X — числа без цифры 0, Y — составные; массив Z; 5 наибольших нечётных в Z; сортировка X, Y, Z.


Задача №2 варианта из методички: операции с массивами по условию в task_02.json.

**Код (`task_02.c`):**

```c
#include <stdio.h>
#include <stdlib.h>

static int has_digit_zero(int x) {
    if (x == 0) {
        return 1;
    }
    if (x < 0) {
        x = -x;
    }
    while (x > 0) {
        if (x % 10 == 0) {
            return 1;
        }
        x /= 10;
    }
    return 0;
}

static int is_composite(int x) {
    if (x < 4) {
        return 0;
    }
    for (int d = 2; d * d <= x; ++d) {
        if (x % d == 0) {
            return 1;
        }
    }
    return 0;
}

static int cmp_int(const void *a, const void *b) {
    int ia = *(const int *)a;
    int ib = *(const int *)b;
    return (ia > ib) - (ia < ib);
}

int main(void) {
    int n, k;
    printf("Введите размер массива X (n): ");
    fflush(stdout);
    if (scanf("%d", &n) != 1 || n < 1) {
        return 1;
    }
    int *x = malloc((size_t)n * sizeof(int));
    printf("Введите %d целых элементов X:\n", n);
    for (int i = 0; i < n; ++i) {
        printf("X[%d]: ", i + 1);
        fflush(stdout);
        if (scanf("%d", &x[i]) != 1) {
            free(x);
            return 1;
        }
    }

    printf("Введите размер массива Y (k): ");
    fflush(stdout);
    if (scanf("%d", &k) != 1 || k < 1) {
        free(x);
        return 1;
    }
    int *y = malloc((size_t)k * sizeof(int));
    printf("Введите %d целых элементов Y:\n", k);
    for (int i = 0; i < k; ++i) {
        printf("Y[%d]: ", i + 1);
        fflush(stdout);
        if (scanf("%d", &y[i]) != 1) {
            free(x);
            free(y);
            return 1;
        }
    }

    int cap = n + k;
    int *z = malloc((size_t)cap * sizeof(int));
    int zlen = 0;
    for (int i = 0; i < n; ++i) {
        if (!has_digit_zero(x[i])) {
            z[zlen++] = x[i];
        }
    }
    for (int i = 0; i < k; ++i) {
        if (is_composite(y[i])) {
            z[zlen++] = y[i];
        }
    }

    int *odds = malloc((size_t)zlen * sizeof(int));
    int oc = 0;
    for (int i = 0; i < zlen; ++i) {
        if (z[i] % 2 != 0) {
            odds[oc++] = z[i];
        }
    }
    qsort(odds, (size_t)oc, sizeof(int), cmp_int);
    int take = oc < 5 ? oc : 5;
    int start = oc - take;

    printf("Пять наибольших нечетных в Z: ");
    for (int i = 0; i < take; ++i) {
        if (i) {
            printf(" ");
        }
        printf("%d", odds[start + i]);
    }
    printf("\n");

    qsort(x, (size_t)n, sizeof(int), cmp_int);
    qsort(y, (size_t)k, sizeof(int), cmp_int);
    qsort(z, (size_t)zlen, sizeof(int), cmp_int);

    printf("X (сорт.): ");
    for (int i = 0; i < n; ++i) {
        if (i) {
            printf(" ");
        }
        printf("%d", x[i]);
    }
    printf("\nY (сорт.): ");
    for (int i = 0; i < k; ++i) {
        if (i) {
            printf(" ");
        }
        printf("%d", y[i]);
    }
    printf("\nZ (сорт.): ");
    for (int i = 0; i < zlen; ++i) {
        if (i) {
            printf(" ");
        }
        printf("%d", z[i]);
    }
    printf("\n");

    free(x);
    free(y);
    free(z);
    free(odds);
    return 0;
}
```

**Ввод:**

```
3
12
21
103
3
4
6
9
```

**Вывод:**

```
Введите размер массива X (n): Введите 3 целых элементов X:
X[1]: X[2]: X[3]: Введите размер массива Y (k): Введите 3 целых элементов Y:
Y[1]: Y[2]: Y[3]: Пять наибольших нечетных в Z: 9 21
X (сорт.): 12 21 103
Y (сорт.): 4 6 9
Z (сорт.): 4 6 9 12 21
```


### Задача №3

**Условие.** Удалить последнюю группу убывающих нечётных чисел.


Задача №3 варианта из методички: операции с массивами по условию в task_03.json.

**Код (`task_03.c`):**

```c
#include <stdio.h>
#include <stdlib.h>

static int is_odd(int x) {
    return x % 2 != 0;
}

static int group_strict_decrease(int *a, int len) {
    if (len < 1) {
        return 0;
    }
    for (int i = 1; i < len; ++i) {
        if (!is_odd(a[i - 1]) || !is_odd(a[i]) || a[i] >= a[i - 1]) {
            return 0;
        }
    }
    return is_odd(a[0]);
}

int main(void) {
    int n;
    printf("Введите размер массива (n): ");
    fflush(stdout);
    if (scanf("%d", &n) != 1 || n < 1) {
        return 1;
    }
    int *a = malloc((size_t)n * sizeof(int));
    printf("Введите %d целых элементов:\n", n);
    for (int i = 0; i < n; ++i) {
        printf("A[%d]: ", i + 1);
        fflush(stdout);
        if (scanf("%d", &a[i]) != 1) {
            free(a);
            return 1;
        }
    }

    int last_start = -1;
    int last_len = 0;
    int i = 0;
    while (i < n) {
        if (!is_odd(a[i])) {
            ++i;
            continue;
        }
        int j = i + 1;
        while (j < n && is_odd(a[j]) && a[j] < a[j - 1]) {
            ++j;
        }
        int len = j - i;
        if (len >= 1 && group_strict_decrease(a + i, len)) {
            last_start = i;
            last_len = len;
        }
        i = (len >= 1) ? j : i + 1;
    }

    if (last_start < 0) {
        printf("Группа не найдена, массив без изменений: ");
        for (int t = 0; t < n; ++t) {
            if (t) {
                printf(" ");
            }
            printf("%d", a[t]);
        }
        printf("\n");
        free(a);
        return 0;
    }

    int newn = n - last_len;
    int *b = malloc((size_t)newn * sizeof(int));
    int p = 0;
    for (int t = 0; t < n; ++t) {
        if (t < last_start || t >= last_start + last_len) {
            b[p++] = a[t];
        }
    }

    printf("Массив после удаления группы (%d элементов): ", newn);
    for (int t = 0; t < newn; ++t) {
        if (t) {
            printf(" ");
        }
        printf("%d", b[t]);
    }
    printf("\n");

    free(a);
    free(b);
    return 0;
}
```

**Ввод:**

```
4
9
7
5
10
```

**Вывод:**

```
Введите размер массива (n): Введите 4 целых элементов:
A[1]: A[2]: A[3]: A[4]: Массив после удаления группы (1 элементов): 10
```


### Задача №4

**Условие.** Упорядочить по возрастанию суммы цифр элементы между последним палиндромом и первым простым.


Задача №4 варианта из методички: операции с массивами по условию в task_04.json.

**Код (`task_04.c`):**

```c
#include <stdio.h>
#include <stdlib.h>

static int digit_sum(int x) {
    if (x < 0) {
        x = -x;
    }
    int s = 0;
    while (x > 0) {
        s += x % 10;
        x /= 10;
    }
    return s;
}

static int is_palindrome(int x) {
    if (x < 0) {
        return 0;
    }
    int o = x, r = 0;
    if (x == 0) {
        return 1;
    }
    while (x > 0) {
        r = r * 10 + x % 10;
        x /= 10;
    }
    return o == r;
}

static int is_prime(int x) {
    if (x < 2) {
        return 0;
    }
    for (int d = 2; d * d <= x; ++d) {
        if (x % d == 0) {
            return 0;
        }
    }
    return 1;
}

typedef struct {
    int val;
    int sum;
} Item;

static int cmp_item(const void *a, const void *b) {
    const Item *ia = a;
    const Item *ib = b;
    if (ia->sum != ib->sum) {
        return ia->sum - ib->sum;
    }
    return ia->val - ib->val;
}

int main(void) {
    int n;
    printf("Введите размер массива (n): ");
    fflush(stdout);
    if (scanf("%d", &n) != 1 || n < 1) {
        return 1;
    }
    int *a = malloc((size_t)n * sizeof(int));
    printf("Введите %d целых элементов:\n", n);
    for (int i = 0; i < n; ++i) {
        printf("A[%d]: ", i + 1);
        fflush(stdout);
        if (scanf("%d", &a[i]) != 1) {
            free(a);
            return 1;
        }
    }

    int last_pal = -1;
    int first_prime = n;
    for (int i = 0; i < n; ++i) {
        if (is_palindrome(a[i])) {
            last_pal = i;
        }
    }
    for (int i = 0; i < n; ++i) {
        if (is_prime(a[i])) {
            first_prime = i;
            break;
        }
    }

    if (last_pal < 0 || first_prime >= n || last_pal + 1 >= first_prime) {
        printf("Нет подходящего интервала, массив: ");
        for (int i = 0; i < n; ++i) {
            if (i) {
                printf(" ");
            }
            printf("%d", a[i]);
        }
        printf("\n");
        free(a);
        return 0;
    }

    int left = last_pal + 1;
    int right = first_prime;
    int m = right - left;
    Item *items = malloc((size_t)m * sizeof(Item));
    for (int i = 0; i < m; ++i) {
        items[i].val = a[left + i];
        items[i].sum = digit_sum(a[left + i]);
    }
    qsort(items, (size_t)m, sizeof(Item), cmp_item);

    int *out = malloc((size_t)n * sizeof(int));
    int p = 0;
    for (int i = 0; i < left; ++i) {
        out[p++] = a[i];
    }
    for (int i = 0; i < m; ++i) {
        out[p++] = items[i].val;
    }
    for (int i = right; i < n; ++i) {
        out[p++] = a[i];
    }

    printf("Результирующий массив: ");
    for (int i = 0; i < p; ++i) {
        if (i) {
            printf(" ");
        }
        printf("%d", out[i]);
    }
    printf("\n");

    free(a);
    free(items);
    free(out);
    return 0;
}
```

**Ввод:**

```
5
4
11
6
5
7
```

**Вывод:**

```
Введите размер массива (n): Введите 5 целых элементов:
A[1]: A[2]: A[3]: A[4]: A[5]: Нет подходящего интервала, массив: 4 11 6 5 7
```
