/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** Test if a string match a globbing pattern
*/

#include "globber.h"

static const glob_handler_t handlers[] = {
    {'*', &handle_asterisk},
    {'?', &handle_qmark},
    {'[', &handle_sqbracket},
    {'\\', &handle_inhibitor}
};

int is_match(const char *pattern, const char *str)
{
    int i = sizeof(handlers) / sizeof(glob_handler_t) - 1;

    if (!pattern || !str) {
        return 0;
    }
    if (!*pattern) {
        return !*str;
    }
    for (; i >= 0; i--) {
        if (handlers[i].c == *pattern) {
            return handlers[i].handler(++pattern, str);
        }
    }
    return handle_default(pattern, str);
}
