/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** Globbing header
*/

#ifndef GLOBBER_H
    #define GLOBBER_H

    typedef struct glob_handler_s {
        char c;
        int (*handler)(const char *, const char *);
    } glob_handler_t;

    int is_match(const char *pattern, const char *str);

    int handle_asterisk(const char *pattern, const char *str);
    int handle_qmark(const char *pattern, const char *str);
    int handle_sqbracket(const char *pattern, const char *str);
    int handle_inhibitor(const char *pattern, const char *str);
    int handle_default(const char *pattern, const char *str);

    int handle_sqbracket_neg(const char *pattern, const char *str);
    int handle_sqbracket_pos(const char *pattern, const char *str);

#endif /* !GLOBBER_H */
