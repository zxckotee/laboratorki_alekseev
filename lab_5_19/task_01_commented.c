/*
 * УЧЕБНАЯ ВЕРСИЯ lab_5_19/task_01.c
 * Лаба 5, вариант 19: группа минимальной длины из простых чисел
 * с строго убывающими цифрами (без массивов — односвязный список).
 *
 * Этот файл не участвует в автотестах; рабочий код — task_01.c
 */

/* Подключаем заголовок: объявления printf, scanf, fflush */
#include <stdio.h>
/* malloc и free — выделение/освобождение памяти под узлы списка */
#include <stdlib.h>
/* Блок ниже только при сборке под Windows (MinGW / MSVC) */
#ifdef _WIN32
#include <windows.h>
#endif

/*
 * struct Node — ОПИСАНИЕ ТИПА «узел списка».
 * struct { ... } создаёт составной тип (как «запись» с полями).
 *
 * typedef ... Node — даёт короткое имя Node вместо struct Node.
 */
typedef struct Node {
    int value;           /* поле: само число (как обычный int) */
    struct Node *next;   /* поле: указатель на СЛЕДУЮЩИЙ узел или NULL (конец) */
    /*
     * struct Node *next читается так:
     *   next — переменная-УКАЗАТЕЛЬ;
     *   она хранит АДРЕС другого узла того же типа;
     *   если список кончился — туда пишем NULL (нигде не указывает).
     */
} Node;

/*
 * list_clear — освобождает ВСЬ список и обнуляет голову.
 *
 * Параметр Node **head — указатель НА ПЕРЕМЕННУЮ-голову (адрес head снаружи).
 * Нужен **, чтобы внутри функции можно было сделать *head = NULL в конце.
 *
 * static — функция видна только в этом .c файле (не для других файлов).
 */
static void list_clear(Node **head) {
    /* Пока голова не пустая: *head — «тот узел, на который смотрит head» */
    while (*head) {
        /* Запоминаем следующий узел, пока текущий ещё жив */
        Node *n = (*head)->next;
        /* Освобождаем память, занятую первым узлом */
        free(*head);
        /* Голова становится следующим; старый узел больше не используем */
        *head = n;
    }
    /* После цикла *head автоматически NULL — список пуст */
}

/*
 * list_push_back — добавить число v В КОНЕЦ списка.
 * head — снова адрес переменной Node * (чтобы менять голову, если список был пуст).
 */
static void list_push_back(Node **head, int v) {
    /* sizeof(Node) — сколько байт занимает одна структура Node */
    Node *n = malloc(sizeof(Node));
    if (!n) {
        /* malloc вернул NULL — памяти нет, выходим тихо */
        return;
    }
    /* Оператор -> : «в узле n поле value» (то же, что (*n).value) */
    n->value = v;
    n->next = NULL; /* новый узел пока «последний» */

    if (!*head) {
        /* Список был пуст: новый узел и есть вся голова */
        *head = n;
        return;
    }

    /* Идём от головы до узла, у которого next == NULL (последний) */
    Node *p = *head;       /* p — «курсор» по списку */
    while (p->next) {      /* пока есть следующий */
        p = p->next;       /* сдвиг курсора вперёд */
    }
    p->next = n;           /* привязали новый узел после последнего */
}

/* Скопировать список src в dest (старый dest уничтожается) */
static void list_copy(Node **dest, Node *src) {
    list_clear(dest);
    /*
     * for (Node *p = src; p; p = p->next) — обход списка:
     *   p = src        — старт с первого узла;
     *   p              — условие: продолжаем, пока p не NULL;
     *   p = p->next    — на каждом шаге переходим к следующему узлу.
     */
    for (Node *p = src; p; p = p->next) {
        list_push_back(dest, p->value);
    }
}

/* Длина списка — сколько узлов */
static int list_len(Node *head) {
    int n = 0;
    for (Node *p = head; p; p = p->next) {
        ++n;
    }
    return n;
}

/* Печать всех value через пробел */
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

/* Проверка: простое ли число (1 — да, 0 — нет) */
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

/*
 * Цифры числа слева направо СТРОГО убывают?
 * Пример: 31 — да (3 > 1), 13 — нет (1 < 3).
 */
static int digits_strictly_decrease(int x) {
    if (x < 0) {
        return 0;
    }
    /* pow10 — степень 10 старшего разряда (1, 10, 100, ...) */
    int pow10 = 1;
    while (x >= pow10 * 10) {
        pow10 *= 10;
    }
    int prev = -1; /* «предыдущая цифра» ещё не задана */
    while (pow10 > 0) {
        int d = x / pow10;
        d %= 10; /* текущая цифра слева */
        if (prev >= 0 && d <= prev) {
            return 0; /* не строго убывает */
        }
        prev = d;
        pow10 /= 10;
    }
    return 1;
}

/* Число подходит в группу: и простое, и цифры убывают */
static int group_fits(int x) {
    return is_prime(x) && digits_strictly_decrease(x);
}

/* void в скобках — у main() нет аргументов командной строки */
int main(void) {
#ifdef _WIN32
    /* Кодовая страница 65001 = UTF-8, чтобы русские буквы в консоли Windows */
    SetConsoleOutputCP(65001);
#endif

    int value; /* очередное введённое число */

    printf("Вводите целые числа (0 — конец последовательности):\n");

    /*
     * Node *current = NULL:
     *   current — указатель на первый узел текущей группы;
     *   NULL — «список пуст, узлов нет».
     *
     * Node *best = NULL — лучшая (самая короткая) найденная группа.
     * best_len — её длина (0 = ещё не нашли).
     */
    Node *current = NULL;
    Node *best = NULL;
    int best_len = 0;

    /* for (;;) — бесконечный цикл; выходим через break */
    for (;;) {
        printf("Введите число: ");
        fflush(stdout); /* сразу показать приглашение до scanf */
        if (scanf("%d", &value) != 1) {
            /* ошибка ввода — подчистить память и выйти с кодом 1 */
            list_clear(&current); /* &current — адрес переменной current */
            list_clear(&best);
            return 1;
        }

        if (value == 0) {
            /* Конец ввода: учесть незакрытую группу current */
            int cur_len = list_len(current);
            if (cur_len > 0 && (best_len == 0 || cur_len < best_len)) {
                best_len = cur_len;
                list_copy(&best, current);
            }
            break;
        }

        if (group_fits(value)) {
            /* Продолжаем накапливать текущую группу */
            list_push_back(&current, value);
        } else {
            /* Группа оборвалась: сравнить с лучшей, начать новую группу */
            int cur_len = list_len(current);
            if (cur_len > 0 && (best_len == 0 || cur_len < best_len)) {
                best_len = cur_len;
                list_copy(&best, current);
            }
            list_clear(&current); /* current снова пустой список */
        }
    }

    list_clear(&current); /* текущая группа больше не нужна */

    if (best_len == 0) {
        printf("Подходящая группа не найдена.\n");
        list_clear(&best);
        return 0;
    }

    printf("Минимальная длина группы: %d\n", best_len);
    printf("Группа: ");
    list_print(best);
    printf("\n");
    list_clear(&best); /* не оставлять утечку памяти */
    return 0;          /* успешное завершение программы */
}
