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

**Условие.** Вводится последовательность из N целых элементов. Для каждого элемента последовательности найти среднее значение его цифр.


Сначала вводится N, затем N целых чисел. Функция `srednee_cifr` берёт модуль числа, в цикле складывает цифры и делит сумму на их количество; для нуля среднее равно 0. В `main` для каждого элемента выводится полученное среднее.

**Код (`task_01.c`):**

```c
#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#endif

double srednee_cifr(int chislo) {
    int modul;
    int summa;
    int kolichestvo;
    int ostatok;

    if (chislo == 0) {
        return 0.0;
    }

    modul = chislo;
    if (modul < 0) {
        modul = -modul;
    }

    summa = 0;
    kolichestvo = 0;
    while (modul > 0) {
        ostatok = modul % 10;
        summa = summa + ostatok;
        kolichestvo = kolichestvo + 1;
        modul = modul / 10;
    }

    return (double)summa / (double)kolichestvo;
}

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif

    int n;
    int i;
    int element;

    printf("Введите N: ");
    fflush(stdout);
    if (scanf("%d", &n) != 1 || n < 1) {
        return 1;
    }

    for (i = 0; i < n; ++i) {
        printf("Введите элемент последовательности: ");
        fflush(stdout);
        if (scanf("%d", &element) != 1) {
            return 1;
        }
        printf("Среднее цифр: %.6f\n", srednee_cifr(element));
    }

    return 0;
}
```

**Ввод:**

```
3
123
-45
0
```

**Вывод:**

```
Введите N: Введите элемент последовательности: Среднее цифр: 2.000000
Введите элемент последовательности: Среднее цифр: 4.500000
Введите элемент последовательности: Среднее цифр: 0.000000
```


### Задача №2

**Условие.** Заданы A и B в системах счисления с основаниями p=2 и q=4. Вычислить C = B³ − 2·B + A и вывести C в десятичной системе и в системе с основанием r=3. Использовать функции.


Числа A и B набираются посимвольно в `prochitat_chislo` без массивов: каждая цифра сразу входит в ответ в соответствующей системе. `vychislit_C` считает B³ − 2B + A. Для троичного вывода `vyvesti_v_sisteme` вызывает себя рекурсивно, печатая цифры слева направо.

**Код (`task_02.c`):**

```c
#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#endif

int simvol_v_cifru(char simvol, int osnovanie) {
    int cifra;

    if (simvol >= '0' && simvol <= '9') {
        cifra = simvol - '0';
    } else if (simvol >= 'A' && simvol <= 'Z') {
        cifra = simvol - 'A' + 10;
    } else if (simvol >= 'a' && simvol <= 'z') {
        cifra = simvol - 'a' + 10;
    } else {
        return -1;
    }

    if (cifra < 0 || cifra >= osnovanie) {
        return -1;
    }
    return cifra;
}

long long prochitat_chislo(int osnovanie) {
    long long znachenie;
    char simvol;
    int cifra;
    int est_cifra;

    znachenie = 0;
    est_cifra = 0;
    while (scanf("%c", &simvol) == 1) {
        if (simvol == '\n' || simvol == ' ' || simvol == '\t' || simvol == '\r') {
            if (est_cifra) {
                break;
            }
            continue;
        }
        cifra = simvol_v_cifru(simvol, osnovanie);
        if (cifra < 0) {
            return -1;
        }
        znachenie = znachenie * osnovanie + cifra;
        est_cifra = 1;
    }

    if (!est_cifra) {
        return -1;
    }
    return znachenie;
}

long long vychislit_C(long long A, long long B) {
    return B * B * B - 2 * B + A;
}

void vyvesti_cifru(long long ost) {
    if (ost < 10) {
        printf("%lld", ost);
    } else {
        printf("%c", (char)('A' + (ost - 10)));
    }
}

void vyvesti_v_sisteme(long long chislo, int osnovanie) {
    if (chislo == 0) {
        return;
    }
    vyvesti_v_sisteme(chislo / osnovanie, osnovanie);
    vyvesti_cifru(chislo % osnovanie);
}

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif

    long long A;
    long long B;
    long long C;
    int p;
    int q;
    int r;

    p = 2;
    q = 4;
    r = 3;

    printf("Введите число A (основание %d): ", p);
    fflush(stdout);
    A = prochitat_chislo(p);
    if (A < 0) {
        printf("Неверная запись числа.\n");
        return 1;
    }

    printf("Введите число B (основание %d): ", q);
    fflush(stdout);
    B = prochitat_chislo(q);
    if (B < 0) {
        printf("Неверная запись числа.\n");
        return 1;
    }

    C = vychislit_C(A, B);

    printf("C в десятичной системе: %lld\n", C);
    printf("C в системе с основанием %d: ", r);
    if (C == 0) {
        printf("0");
    } else {
        vyvesti_v_sisteme(C, r);
    }
    printf("\n");

    return 0;
}
```

**Ввод:**

```
101
20
```

**Вывод:**

```
Введите число A (основание 2): Введите число B (основание 4): C в десятичной системе: 501
C в системе с основанием 3: 200120
```
