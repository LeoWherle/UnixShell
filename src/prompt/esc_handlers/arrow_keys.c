/*
** EPITECH PROJECT, 2023
** 42sh [WSL: fedora]
** File description:
** arrows
*/

#include <stdio.h>
#include <string.h>
#include "errorh.h"
#include "prompt.h"

int up_arrow(UNUSED textfield_t *field, UNUSED char seq[])
{
    return 0;
}

int down_arrow(UNUSED textfield_t *field, UNUSED char seq[])
{
    return 0;
}

int right_arrow(textfield_t *field, UNUSED char seq[])
{
    if (field->cursor_pos < strlen(field->buffer)) {
        field->cursor_pos++;
    }
    return 0;
}

int left_arrow(textfield_t *field, UNUSED char seq[])
{
    if (field->cursor_pos > 0) {
        field->cursor_pos--;
    }
    return 0;
}
