/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** history
*/

#include <stdbool.h>
#include "clist.h"

#ifndef HISTORY_H
    #define HISTORY_H

    typedef struct history {
        int nb;
        char *time;
        char *command;
    } history_t;

    typedef struct h_flag {
        bool clear;
        bool simple;
        bool horodates;
        bool reverse;
    } h_flag_t;
    
    history_t *history_create(char *command);
    void histroy_destroy(void *ptr);
    void print_history(list_t *history, int i, h_flag_t *flag);
    char *find_com_in_history(list_t *history, char *to_find);
    int my_history(char **command, head_t *head, int *return_value);

#endif /* HISTORY_H */