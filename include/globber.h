/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** Globbing header
*/

#ifndef GLOBBER_H
    #define GLOBBER_H
    #define IS_GLOCHAR(c) (c == '*' || c == '?' || c == '[')
    #define IS_INRANGE(c, s, e) ((c >= s && c <= e) || (c >= e && c <= s))
    #include "clist.h"

    typedef struct glob_handler_s {
        char c;
        int (*handler)(const char *, const char *);
    } glob_handler_t;

    list_t *reslist_from_ppattern(char **elems, const char *prefix, int depth);

    void any_concerned(list_t *list, const char *pattern,
        const char *prefix, const char *entryn);
    void dir_concerned(list_t *list, const char *pattern,
        const char *prefix, const char *entryn);
    list_t *get_concerned(const char *pattern, const char *prefix,
        void (*assert)(list_t *, const char *, const char *, const char *));

    void sort_matches(node_t *head);
    void move_dirs_to_end(list_t *matches);

    char *str_from_list(list_t *list);
    void add_prefix_to_list(list_t *list, const char *prefix);
    void insert_list_in_tab(char ***tab, list_t *list, int i);
    char **list_to_tab(list_t *list);

    char **parse_pattern(const char *pattern);
    void add_prefix_to_str(char **str, const char *prefix);
    int is_valid_pattern(const char *pattern);

    int is_match(const char *pattern, const char *str);

    int handle_asterisk(const char *pattern, const char *str);
    int handle_qmark(const char *pattern, const char *str);
    int handle_sqbracket(const char *pattern, const char *str);
    int handle_inhibitor(const char *pattern, const char *str);
    int handle_default(const char *pattern, const char *str);

    int handle_sqbracket_neg(const char *pattern, const char *str);
    int handle_sqbracket_pos(const char *pattern, const char *str);

#endif /* !GLOBBER_H */
