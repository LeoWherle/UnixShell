/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** alias header
*/

#include "clist.h"

#ifndef RC_H
    #define RC_H

    typedef struct alias {
        char *alias;
        char *command;
    } alias_t;

    list_t *get_alias_list(void);
    char *get_alias(char *command_part, list_t *aliases);

#endif /* !ALIAS_H */
