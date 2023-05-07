/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** history up down
*/

#include <stddef.h>
#include "history.h"
#include "mysh.h"

char *history_up_down(bool ud, head_t *head, bool reset)
{
    static node_t *actual = NULL;
    history_t *line = NULL;

    if (reset) {
        actual = NULL;
        return;
    }
    if (!actual)
        actual = head->history->tail;
    if (ud) {
        actual = actual->prev;
    } else {
        actual = actual->next;
    }
}
