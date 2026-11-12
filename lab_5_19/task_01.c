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
