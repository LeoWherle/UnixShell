/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** alias header
*/

#include "clist.h"

#ifndef RC_H
    #define RC_H

    #define IS_ALIAS(line) line[0] == 'a' && line[1] == 'l' \
&& line[2] == 'i' && line[3] == 'a' && line[4] == 's'

    typedef struct alias {
        char *alias;
        char *command;
    } alias_t;

    char *change_command(char *command, list_t *aliases);
    list_t *get_alias_list(void);

#endif /* !ALIAS_H */
