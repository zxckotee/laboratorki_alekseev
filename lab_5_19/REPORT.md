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
#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#endif


typedef struct Node {
    int value;
    struct Node *next;
} Node;

static void list_clear(Node **head) {
    while (*head) {
        Node *n = (*head)->next;
        free(*head);
        *head = n;
    }
}

static void list_push_back(Node **head, int v) {
    Node *n = malloc(sizeof(Node));
    if (!n) {
        return;
    }
    n->value = v;
    n->next = NULL;
    if (!*head) {
        *head = n;
        return;
    }
    Node *p = *head;
    while (p->next) {
        p = p->next;
    }
    p->next = n;
}

static void list_copy(Node **dest, Node *src) {
    list_clear(dest);
    for (Node *p = src; p; p = p->next) {
        list_push_back(dest, p->value);
    }
}

static int list_len(Node *head) {
    int n = 0;
    for (Node *p = head; p; p = p->next) {
        ++n;
    }
    return n;
}

static void list_print(Node *head) {
    int first = 1;
    for (Node *p = head; p; p = p->next) {
        if (!first) {
            printf(" ");
        }
        printf("%d", p->value);
        first = 0;
    }
}

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

static int digits_strictly_decrease(int x) {
    if (x < 0) {
        return 0;
    }
    int pow10 = 1;
    while (x >= pow10 * 10) {
        pow10 *= 10;
    }
    int prev = -1;
    while (pow10 > 0) {
        int d = x / pow10;
        d %= 10;
        if (prev >= 0 && d <= prev) {
            return 0;
        }
        prev = d;
        pow10 /= 10;
    }
    return 1;
}

static int group_fits(int x) {
    return is_prime(x) && digits_strictly_decrease(x);
}

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif

    int value;

    printf("Вводите целые числа (0 — конец последовательности):\n");

    Node *current = NULL;
    Node *best = NULL;
    int best_len = 0;

    for (;;) {
        printf("Введите число: ");
        fflush(stdout);
        if (scanf("%d", &value) != 1) {
            list_clear(&current);
            list_clear(&best);
            return 1;
        }
        if (value == 0) {
            int cur_len = list_len(current);
            if (cur_len > 0 && (best_len == 0 || cur_len < best_len)) {
                best_len = cur_len;
                list_copy(&best, current);
            }
            break;
        }

        if (group_fits(value)) {
            list_push_back(&current, value);
        } else {
            int cur_len = list_len(current);
            if (cur_len > 0 && (best_len == 0 || cur_len < best_len)) {
                best_len = cur_len;
                list_copy(&best, current);
            }
            list_clear(&current);
        }
    }

    list_clear(&current);

    if (best_len == 0) {
        printf("Подходящая группа не найдена.\n");
        list_clear(&best);
        return 0;
    }

    printf("Минимальная длина группы: %d\n", best_len);
    printf("Группа: ");
    list_print(best);
    printf("\n");
    list_clear(&best);
    return 0;
}
```

**Ввод:**

```
73
31
53
0
```

**Вывод:**

```
Вводите целые числа (0 — конец последовательности):
Введите число: Введите число: Введите число: Введите число: Подходящая группа не найдена.
```
