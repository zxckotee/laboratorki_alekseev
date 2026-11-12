/* Корректный вывод кириллицы в консоли Windows (UTF-8). На Linux — no-op. */
#ifndef LAB_CONSOLE_H
#define LAB_CONSOLE_H

#ifdef _WIN32
#include <windows.h>

static inline void lab_console_utf8(void) {
    SetConsoleOutputCP(65001);
}
#else
static inline void lab_console_utf8(void) {}
#endif

#endif
