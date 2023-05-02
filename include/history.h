/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** history
*/

#include "clist.h"

#ifndef HISTORY_H
    #define HISTORY_H

    typedef struct history {
        int nb;
        char *time;
        char *command;
    } history_t;
    
    history_t *history_create(char *command);
    void histroy_destroy(void *ptr);
    void print_history(list_t *history);
    char *find_com_in_history(list_t *history, char *to_find);

#endif /* HISTORY_H */