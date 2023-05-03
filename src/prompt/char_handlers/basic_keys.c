/*
** EPITECH PROJECT, 2023
** 42sh [WSL: fedora]
** File description:
** basic_keys
*/

#include <string.h>
#include <stdio.h>
#include "prompt.h"
#include "errorh.h"

int enter_key(UNUSED textfield_t *field)
{
    putchar('\n');
    return 1;
}

int tab_key(UNUSED textfield_t *field)
{
    return 0;
}

int backspace_key(textfield_t *field)
{
    if (field->cursor_pos > 0) {
        memmove(field->buffer + field->cursor_pos - 1,
            field->buffer + field->cursor_pos,
            field->bf_size - field->cursor_pos + 1);
        (field->cursor_pos)--;
        field->bf_size--;
    }
    return 0;
}
