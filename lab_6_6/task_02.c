#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#endif

typedef struct Node {
    int value;
    struct Node *next;
} Node;

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

static void list_clear(Node **head) {
    while (*head) {
        Node *n = (*head)->next;
        free(*head);
        *head = n;
    }
}

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
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif

    int need;

    printf("Введите количество палиндромов n: ");
    fflush(stdout);
    if (scanf("%d", &need) != 1 || need < 1) {
        return 1;
    }

    Node *head = NULL;
    int pal_count = 0;

    while (pal_count < need) {
        printf("Введите целое число: ");
        fflush(stdout);
        int value;
        if (scanf("%d", &value) != 1) {
            list_clear(&head);
            return 1;
        }
        list_push_back(&head, value);
        if (is_palindrome(value)) {
            ++pal_count;
        }
    }

    printf("В восьмеричной системе счисления: ");
    int first = 1;
    for (Node *p = head; p; p = p->next) {
        if (!first) {
            printf(" ");
        }
        printf("%o", p->value);
        first = 0;
    }
    printf("\n");

    list_clear(&head);
    return 0;
}
