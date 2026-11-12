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

## Лабораторная работа 8

Вариант **19**. Факультет математики и компьютерных наук, Фундаментальная математика и механика.


### Задача №1

**Условие.** Произведение кратных 7; количество между первым и последним чётным; Y из первых k положительных; удалить из X элемент, ближайший к среднему.


Задача №1 варианта из методички: операции с массивами по условию в task_01.json.

**Код (`task_01.c`):**

```c
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n, k;
    printf("Введите размер массива X (n): ");
    fflush(stdout);
    if (scanf("%d", &n) != 1 || n < 1) return 1;

    int *x = malloc((size_t)n * sizeof(int));
    printf("Введите %d целых элементов X:\n", n);
    for (int i = 0; i < n; ++i) {
        printf("X[%d]: ", i + 1);
        fflush(stdout);
        if (scanf("%d", &x[i]) != 1) { free(x); return 1; }
    }

    long long prod7 = 1;
    int has7 = 0;
    for (int i = 0; i < n; ++i) {
        if (x[i] != 0 && x[i] % 7 == 0) {
            prod7 *= x[i];
            has7 = 1;
        }
    }
    if (!has7) prod7 = 0;

    int fe = -1, le = -1;
    for (int i = 0; i < n; ++i) {
        if (x[i] % 2 == 0) {
            if (fe < 0) fe = i;
            le = i;
        }
    }
    int between = 0;
    if (fe >= 0 && le > fe) between = le - fe - 1;

    printf("Произведение кратных 7: %lld\n", prod7);
    printf("Количество между первым и последним четным: %d\n", between);

    printf("Введите k (число положительных для Y): ");
    fflush(stdout);
    if (scanf("%d", &k) != 1 || k < 0) { free(x); return 1; }

    int *y = malloc((size_t)n * sizeof(int));
    int ylen = 0;
    for (int i = 0; i < n && ylen < k; ++i) {
        if (x[i] > 0) y[ylen++] = x[i];
    }

    printf("Массив Y (%d): ", ylen);
    for (int i = 0; i < ylen; ++i) {
        if (i) printf(" ");
        printf("%d", y[i]);
    }
    printf("\n");

    double mean = 0.0;
    for (int i = 0; i < n; ++i) mean += x[i];
    mean /= (double)n;

    int best = 0;
    double best_d = fabs(x[0] - mean);
    for (int i = 1; i < n; ++i) {
        double d = fabs(x[i] - mean);
        if (d < best_d - 1e-9 || (fabs(d - best_d) < 1e-9 && i < best)) {
            best_d = d;
            best = i;
        }
    }
    int *xn = malloc((size_t)(n - 1) * sizeof(int));
    int p = 0;
    for (int i = 0; i < n; ++i) {
        if (i != best) xn[p++] = x[i];
    }
    printf("X после удаления элемента, ближайшего к среднему (%.3f):\n", mean);
    for (int i = 0; i < p; ++i) {
        if (i) printf(" ");
        printf("%d", xn[i]);
    }
    printf("\n");

    free(x); free(y); free(xn);
    return 0;
}
```

**Ввод:**

```
5
7
14
3
8
4
2
```

**Вывод:**

```
Введите размер массива X (n): Введите 5 целых элементов X:
X[1]: X[2]: X[3]: X[4]: X[5]: Произведение кратных 7: 98
Количество между первым и последним четным: 2
Введите k (число положительных для Y): Массив Y (2): 7 14
X после удаления элемента, ближайшего к среднему (7.200):
14 3 8 4
```


### Задача №2

**Условие.** X в пятеричной, Y в шестеричной записи → Z в десятичной; пять наибольших с нечётной суммой цифр.


Задача №2 варианта из методички: операции с массивами по условию в task_02.json.

**Код (`task_02.c`):**

```c
#include <stdio.h>
#include <stdlib.h>

static int from_base_representation(int code, int base) {
    int sign = 1;
    if (code < 0) { sign = -1; code = -code; }
    int result = 0;
    int pow = 1;
    while (code > 0) {
        int d = code % 10;
        if (d >= base) return 0;
        result += d * pow;
        pow *= base;
        code /= 10;
    }
    return sign * result;
}

static int digit_sum(int x) {
    if (x < 0) x = -x;
    int s = 0;
    while (x > 0) { s += x % 10; x /= 10; }
    return s;
}

static int cmp_desc(const void *a, const void *b) {
    int ia = *(const int *)a, ib = *(const int *)b;
    return (ib > ia) - (ib < ia);
}

int main(void) {
    int n, k;
    printf("Введите размер массива X (n): ");
    fflush(stdout);
    if (scanf("%d", &n) != 1 || n < 1) return 1;

    int *z = malloc((size_t)(n + 256) * sizeof(int));
    int zlen = 0;

    printf("Введите %d чисел в пятеричной записи:\n", n);
    for (int i = 0; i < n; ++i) {
        int code;
        printf("X[%d]: ", i + 1);
        fflush(stdout);
        if (scanf("%d", &code) != 1) { free(z); return 1; }
        z[zlen++] = from_base_representation(code, 5);
    }

    printf("Введите размер массива Y (k): ");
    fflush(stdout);
    if (scanf("%d", &k) != 1 || k < 1) { free(z); return 1; }

    printf("Введите %d чисел в шестеричной записи:\n", k);
    for (int i = 0; i < k; ++i) {
        int code;
        printf("Y[%d]: ", i + 1);
        fflush(stdout);
        if (scanf("%d", &code) != 1) { free(z); return 1; }
        z[zlen++] = from_base_representation(code, 6);
    }

    int *cand = malloc((size_t)zlen * sizeof(int));
    int cc = 0;
    for (int i = 0; i < zlen; ++i) {
        if (digit_sum(z[i]) % 2 != 0) cand[cc++] = z[i];
    }
    qsort(cand, (size_t)cc, sizeof(int), cmp_desc);

    int take = cc < 5 ? cc : 5;
    printf("Z (десятичный, %d элементов): ", zlen);
    for (int i = 0; i < zlen; ++i) {
        if (i) printf(" ");
        printf("%d", z[i]);
    }
    printf("\nПять наибольших с нечетной суммой цифр: ");
    for (int i = 0; i < take; ++i) {
        if (i) printf(" ");
        printf("%d", cand[i]);
    }
    printf("\n");

    free(z); free(cand);
    return 0;
}
```

**Ввод:**

```
2
23
10
2
15
14
```

**Вывод:**

```
Введите размер массива X (n): Введите 2 чисел в пятеричной записи:
X[1]: X[2]: Введите размер массива Y (k): Введите 2 чисел в шестеричной записи:
Y[1]: Y[2]: Z (десятичный, 4 элементов): 13 5 11 10
Пять наибольших с нечетной суммой цифр: 10 5
```


### Задача №3

**Условие.** Удалить группу простых минимальной длины с убывающими цифрами.


Задача №3 варианта из методички: операции с массивами по условию в task_03.json.

**Код (`task_03.c`):**

```c
#include <stdio.h>
#include <stdlib.h>

static int is_prime(int x) {
    if (x < 2) return 0;
    for (int d = 2; d * d <= x; ++d)
        if (x % d == 0) return 0;
    return 1;
}

static int digits_strict_decrease(int x) {
    if (x < 0) return 0;
    int pow10 = 1;
    while (x >= pow10 * 10) pow10 *= 10;
    int prev = -1;
    while (pow10 > 0) {
        int d = (x / pow10) % 10;
        if (prev >= 0 && d >= prev) return 0;
        prev = d;
        pow10 /= 10;
    }
    return 1;
}

int main(void) {
    int n;
    printf("Введите размер массива (n): ");
    fflush(stdout);
    if (scanf("%d", &n) != 1 || n < 1) return 1;

    int *a = malloc((size_t)n * sizeof(int));
    printf("Введите %d целых элементов:\n", n);
    for (int i = 0; i < n; ++i) {
        printf("A[%d]: ", i + 1);
        fflush(stdout);
        if (scanf("%d", &a[i]) != 1) { free(a); return 1; }
    }

    int best_s = -1, best_len = n + 1, best_i = -1;
    int i = 0;
    while (i < n) {
        if (!is_prime(a[i])) { ++i; continue; }
        int j = i + 1;
        while (j < n && is_prime(a[j]) && digits_strict_decrease(a[j])) ++j;
        int len = j - i;
        if (len >= 1 && digits_strict_decrease(a[i])) {
            if (len < best_len || (len == best_len && i < best_s)) {
                best_len = len;
                best_s = i;
                best_i = i;
            }
        }
        i = j > i ? j : i + 1;
    }

    if (best_i < 0) {
        printf("Группа не найдена: ");
        for (int t = 0; t < n; ++t) { if (t) printf(" "); printf("%d", a[t]); }
        printf("\n");
        free(a);
        return 0;
    }

    int newn = n - best_len;
    int *b = malloc((size_t)newn * sizeof(int));
    int p = 0;
    for (int t = 0; t < n; ++t) {
        if (t < best_i || t >= best_i + best_len) b[p++] = a[t];
    }
    printf("Массив после удаления группы (%d элементов): ", p);
    for (int t = 0; t < p; ++t) { if (t) printf(" "); printf("%d", b[t]); }
    printf("\n");

    free(a); free(b);
    return 0;
}
```

**Ввод:**

```
4
13
31
2
5
```

**Вывод:**

```
Введите размер массива (n): Введите 4 целых элементов:
A[1]: A[2]: A[3]: A[4]: Группа не найдена: 13 31 2 5
```


### Задача №4

**Условие.** Упорядочить по убыванию суммы цифр между последним и предпоследним палиндромами.


Задача №4 варианта из методички: операции с массивами по условию в task_04.json.

**Код (`task_04.c`):**

```c
#include <stdio.h>
#include <stdlib.h>

static int digit_sum(int x) {
    if (x < 0) x = -x;
    int s = 0;
    while (x > 0) { s += x % 10; x /= 10; }
    return s;
}

static int is_palindrome(int x) {
    if (x < 0) return 0;
    int o = x, r = 0;
    if (x == 0) return 1;
    while (x > 0) { r = r * 10 + x % 10; x /= 10; }
    return o == r;
}

typedef struct { int val; int sum; } Item;

static int cmp_item_desc(const void *a, const void *b) {
    const Item *ia = a, *ib = b;
    if (ia->sum != ib->sum) return ib->sum - ia->sum;
    return ib->val - ia->val;
}

int main(void) {
    int n;
    printf("Введите размер массива (n): ");
    fflush(stdout);
    if (scanf("%d", &n) != 1 || n < 1) return 1;

    int *a = malloc((size_t)n * sizeof(int));
    printf("Введите %d целых элементов:\n", n);
    for (int i = 0; i < n; ++i) {
        printf("A[%d]: ", i + 1);
        fflush(stdout);
        if (scanf("%d", &a[i]) != 1) { free(a); return 1; }
    }

    int pal_pos[256];
    int pc = 0;
    for (int i = 0; i < n; ++i) {
        if (is_palindrome(a[i]) && pc < 256) pal_pos[pc++] = i;
    }

    if (pc < 2) {
        printf("Недостаточно палиндромов, массив: ");
        for (int i = 0; i < n; ++i) { if (i) printf(" "); printf("%d", a[i]); }
        printf("\n");
        free(a);
        return 0;
    }

    int left = pal_pos[pc - 2] + 1;
    int right = pal_pos[pc - 1];
    if (left >= right) {
        printf("Пустой интервал, массив: ");
        for (int i = 0; i < n; ++i) { if (i) printf(" "); printf("%d", a[i]); }
        printf("\n");
        free(a);
        return 0;
    }

    int m = right - left;
    Item *items = malloc((size_t)m * sizeof(Item));
    for (int i = 0; i < m; ++i) {
        items[i].val = a[left + i];
        items[i].sum = digit_sum(a[left + i]);
    }
    qsort(items, (size_t)m, sizeof(Item), cmp_item_desc);

    int out[512];
    int p = 0;
    for (int i = 0; i < left; ++i) out[p++] = a[i];
    for (int i = 0; i < m; ++i) out[p++] = items[i].val;
    for (int i = right; i < n; ++i) out[p++] = a[i];

    printf("Результирующий массив: ");
    for (int i = 0; i < p; ++i) { if (i) printf(" "); printf("%d", out[i]); }
    printf("\n");

    free(a); free(items);
    return 0;
}
```

**Ввод:**

```
6
1
121
13
5
22
3
```

**Вывод:**

```
Введите размер массива (n): Введите 6 целых элементов:
A[1]: A[2]: A[3]: A[4]: A[5]: A[6]: Пустой интервал, массив: 1 121 13 5 22 3
```
