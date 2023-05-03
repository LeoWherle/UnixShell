/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** print history
*/

#include <stdio.h>
#include <stddef.h>
#include "clist.h"
#include "history.h"

static void clear_history(list_t *list)
{
    while (list->head)
        node_destroy(list, histroy_destroy);
}

void print_flag(history_t *line, h_flag_t *flag)
{
    if (flag->simple && flag->horodates)
        printf("#+%s\n", line->horodate);
    if (!flag->simple)
        printf("    %d  %s   %s\n", line->nb, line->time, line->command);
    else
        printf("%s\n", line->command);
}

void print_history(list_t *history, int i, h_flag_t *flag)
{
    history_t *line = NULL;
    node_t *node = history->tail;
    if (flag->clear) {
        clear_history(history);
        return;
    }
    if (!flag->reverse) {
        for (;i > 1 && node->prev; i--)
            node = node->prev;
        for (; node; node = node->next) {
            line = node->data;
            print_flag(line, flag);
        }
    } else  {
        for (; i > 0 && node; i--) {
            line = node->data;
            print_flag(line, flag);
            node = node->prev;
        }
    }
}

void recall_error(char **d_command, int i, int j, bool *error)
{
    *error = true;
    fprintf(stderr, "%s: Event not found.\n", &d_command[i][j]);
    d_command[i][j] = '\0';
    for (; d_command[i]; i++)
        d_command[i][0] = '\0';
}
