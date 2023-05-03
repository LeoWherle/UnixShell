/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** Globbing header
*/

#ifndef GLOBBER_H
    #define GLOBBER_H
    #include "clist.h"

    typedef struct glob_handler_s {
        char c;
        int (*handler)(const char *, const char *);
    } glob_handler_t;

    list_t *reslist_from_ppattern(list_t *elems, const char *prefix);
    char *get_all_matches(const char *pattern);

    list_t *get_contained_matching(const char *pattern, const char *prefix);
    list_t *get_dir_contained_matching(const char *pattern, const char *prefix);
    void rec_match_find(list_t *elems, list_t *res);

    list_t *parse_pattern(const char *pattern);
    char *str_from_list(list_t *list);
    void add_prefix_to_list(list_t *list, const char *prefix);

    int is_match(const char *pattern, const char *str);

    int handle_asterisk(const char *pattern, const char *str);
    int handle_qmark(const char *pattern, const char *str);
    int handle_sqbracket(const char *pattern, const char *str);
    int handle_inhibitor(const char *pattern, const char *str);
    int handle_default(const char *pattern, const char *str);

    int handle_sqbracket_neg(const char *pattern, const char *str);
    int handle_sqbracket_pos(const char *pattern, const char *str);

#endif /* !GLOBBER_H */
