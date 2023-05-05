/*
** EPITECH PROJECT, 2023
** 42sh [WSL: fedora]
** File description:
** arrows
*/

#include <stdio.h>
#include <string.h>
#include "errorh.h"
#include "mystr.h"
#include "mysh.h"
#include "history.h"
#include "clist.h"
#include "prompt.h"

int up_arrow(textfield_t *field, UNUSED char seq[], head_t *head)
{
    node_t *node = NULL;
    history_t *history = NULL;

    ASSERT_PTR(head->history, 0);
    node = head->history->tail;
    ASSERT_PTR(node, 0);
    history = node->data;
    strcpy(field->buffer, history->command);
    field->bf_size = strlen(field->buffer);
    field->cursor_pos = strlen(field->buffer);
    return 0;
}

int down_arrow(UNUSED textfield_t *field, UNUSED char seq[], head_t *head)
{
    return 0;
}

int right_arrow(textfield_t *field, UNUSED char seq[], UNUSED head_t *head)
{
    if (field->cursor_pos < field->bf_size) {
        field->cursor_pos++;
    }
    return 0;
}

int left_arrow(textfield_t *field, UNUSED char seq[], UNUSED head_t *head)
{
    if (field->cursor_pos > 0) {
        field->cursor_pos--;
    }
    return 0;
}
