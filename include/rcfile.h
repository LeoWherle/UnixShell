/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** alias header
*/

#ifndef RC_H
    #define RC_H

    typedef struct alias {
        char *alias;
        char *command;
    } alias_t;

    char *change_command(char *command, alias_t **aliases);
    alias_t **get_alias_list(void);

#endif /* !ALIAS_H */
