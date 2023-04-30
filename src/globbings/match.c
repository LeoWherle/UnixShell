/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** Test if a string match a globbing pattern
*/

#include "globber.h"

int is_match(const char *pattern, const char *str)
{
    if (!pattern || !str) {
        return 0;
    }
    switch (*pattern) {
        case '\0': return *str ? 0 : 1;
        case '*': return handle_asterisk(++pattern, str);
        case '?': return handle_qmark(++pattern, str);
        case '[': return handle_sqbracket(++pattern, str);
        case '\\': return handle_inhibitor(++pattern, str);
        default: break;
    }
    if (*pattern == *str) {
        return is_match(++pattern, ++str);
    }
    return 0;
}
