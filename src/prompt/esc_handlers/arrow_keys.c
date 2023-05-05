/*
** EPITECH PROJECT, 2023
** 42sh [WSL: fedora]
** File description:
** arrows
*/

#include <stdio.h>
#include <string.h>
#include "clist.h"
#include "errorh.h"
#include "history.h"
#include "mysh.h"
#include "mystr.h"
#include "prompt.h"

static void set_current_history(textfield_t *field, head_t *head)
{
    node_t *node = head->history->tail;
    history_t *history = NULL;
    unsigned int i = 0;

    for (i = 0; i < field->history_pos && node->prev; i++) {
        node = node->prev;
    }
    history = node->data;
    strcpy(field->buffer, history->command);
    field->bf_size = strlen(field->buffer);
    field->cursor_pos = field->bf_size;
}

int up_arrow(textfield_t *field, UNUSED char seq[], head_t *head)
{
    ASSERT_PTR(head->history, 0);
    ASSERT_PTR(head->history->tail, 0);
    memset(field->buffer, 0, sizeof(char) * MAX_INPUTLINE);
    set_current_history(field, head);
    if (head->history->size - 1 > (int) field->history_pos) {
        field->history_pos++;
    }
    return 0;
}

int down_arrow(textfield_t *field, UNUSED char seq[], head_t *head)
{
    ASSERT_PTR(head->history, 0);
    ASSERT_PTR(head->history->tail, 0);
    memset(field->buffer, 0, sizeof(char) * MAX_INPUTLINE);
    if (field->history_pos > 0) {
        field->history_pos--;
        set_current_history(field, head);
        return 0;
    }
    field->bf_size = 0;
    field->cursor_pos = 0;
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
