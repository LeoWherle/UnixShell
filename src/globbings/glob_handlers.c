/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** Handlers for different globbing patterns
*/

#include "globber.h"

int handle_asterisk(const char *pattern, const char *str)
{
    if (!*pattern && !*str) {
        return 0;
    }
    while (*str) {
        if (is_match(pattern, ++str)) {
            return 1;
        }
    }
    return is_match(pattern, str);
}

int handle_qmark(const char *pattern, const char *str)
{
    if (*str) {
        return is_match(pattern, str + 1);
    }
    return 0;
}

/*
int handle_sqbracket(const char *pattern, const char *str)
{
    switch (*pattern) {
        case '\0': return 0;
        case ']': return is_match(++pattern, str + 1);
        case '^': return handle_sqbracket_neg(++pattern, str);
        case '[': return 0; // TODO : Add nested sqbrackets
        default : return handle_sqbracket_pos(pattern, str);
    }
}
*/

int handle_inhibitor(const char *pattern, const char *str)
{
    if (*str && *pattern == *str) {
        return is_match(pattern + 1, str + 1);
    }
    return 0;
}
