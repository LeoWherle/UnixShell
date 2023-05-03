/*
** EPITECH PROJECT, 2023
** 42sh [WSL: fedora]
** File description:
** extra_keys
*/

#include <stdio.h>
#include <string.h>
#include "prompt.h"

int delete_key(textfield_t *field, char seq[])
{
    if (seq[1] == '~') {
        if (field->cursor_pos < strlen(field->buffer)) {
            memmove(field->buffer + field->cursor_pos,
                field->buffer + field->cursor_pos + 1,
                strlen(field->buffer) - field->cursor_pos);
            field->bf_size--;
        }
    }
    return 0;
}
