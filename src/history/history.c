/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** history
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "history.h"
#include "errorh.h"
#include "clist.h"
#include "mysh.h"

history_t *history_create(char *command)
{
    static int nb = 0;
    history_t *new = NULL;
    time_t rawtime = {0};
    struct tm *timeinfo = NULL;
    char *date = NULL;

    new = malloc(sizeof(history_t));
    ASSERT_MALLOC(new, NULL);
    new->command = strdup(command);
    ASSERT_MALLOC(new->command, NULL);
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    date = asctime(timeinfo);
    new->time = strndup(&date[10], 6);
    ASSERT_MALLOC(new->time, NULL);
    new->horodate = NULL;
    new->nb = nb;
    nb++;
    return new;
}

void histroy_destroy(void *ptr)
{
    history_t *history = ptr;

    free(history->command);
    free(history->time);
    if (history->horodate)
        free(history->horodate);
    free(history);
}

char *find_com_in_history(list_t *history, char *to_find)
{
    history_t *line = NULL;
    int len = 0;

    len = strlen(to_find);
    for (node_t *node = history->tail; node; node = node->prev) {
        line = node->data;
        if (strncmp(line->command, to_find, len) == 0)
            return line->command;
    }
    return NULL;
}
