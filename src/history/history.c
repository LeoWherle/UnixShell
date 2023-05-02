/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** history
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "history.h"
#include "errorh.h"
#include "clist.h"

history_t *history_create(char *command)
{
    static int nb = 0;
    history_t *new = NULL;
    time_t rawtime = {0};
    struct tm *timeinfo = NULL;

    new = malloc(sizeof(history_t));
    ASSERT_MALLOC(new, NULL);
    new->command = strdup(command);
    ASSERT_MALLOC(new->command, NULL);
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    new->time = asctime(timeinfo);
    ASSERT_MALLOC(new->time, NULL);
    free(timeinfo);
    new->nb = nb;
    nb++;
    return new;
}

void histroy_destroy(void *ptr)
{
    history_t *history = ptr;

    free(history->command);
    free(history->time);
    free(history);
}

void print_history(list_t *history)
{
    history_t *line = NULL;

    for (node_t *node = history->head; node; node = node->next) {
        line = node->data;
        printf("\t%d\t%s\t%s\n", line->nb, line->time, line->command);
    }
}

char *find_com_in_history(list_t *history, char *to_find)
{
    history_t *line = NULL;
    int len = 0;

    len = strlen(to_find);
    for (node_t *node = history->head; node; node = node->next) {
        line = node->data;
        if (strncmp(line->command, to_find, len) == 0)
            return line->command;
    }
    return NULL;
}
