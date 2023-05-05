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

char *get_time(time_t *rawtime)
{
    struct tm *timeinfo = NULL;
    char *date = NULL;
    int dec = 11;
    int size = 5;

    timeinfo = localtime(rawtime);
    date = asctime(timeinfo);
    if (date[dec] == '0') {
        dec++;
        size--;
    }
    return strndup(&date[dec], size);
}

history_t *history_create(char *command)
{
    static int nb = 1;
    history_t *new = NULL;
    time_t rawtime = {0};

    time(&rawtime);
    new = malloc(sizeof(history_t));
    ASSERT_MALLOC(new, NULL);
    new->command = strdup(command);
    ASSERT_MALLOC(new->command, NULL);
    new->time = get_time(&rawtime);
    ASSERT_MALLOC(new->time, NULL);
    new->horodate = rawtime;
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
