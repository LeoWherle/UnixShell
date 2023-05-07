/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** add to history
*/

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "clist.h"
#include "history.h"

char *add_to_history(char *new_command, head_t *head)
{
    history_t *new = NULL;
    history_t *prev = NULL;
    node_t *node = NULL;

    if (head->history->size > 0) {
        prev = head->history->tail->data;
        if (strcmp(prev->command, new_command) == 0) {
            node = head->history->tail;
            node_delete(head->history, prev, histroy_destroy);
            free(node);
        }
    }
    new = history_create(new_command);
    if (!new || node_append(head->history, new) == 1) {
        head->keep = false;
        head->lr = 84;
        return NULL;
    }
    return new_command;
}
