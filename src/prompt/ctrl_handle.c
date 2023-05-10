/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** ctrl_handle
*/

#include <ctype.h>
#include "mystr.h"
#include "prompt.h"

int ctrl_right_arrow(textfield_t *field, UNUSED char seq[], UNUSED head_t *head)
{
    while (field->cursor_pos < field->bf_size &&
    !isalnum(field->buffer[field->cursor_pos]))
        field->cursor_pos++;
    while (field->cursor_pos < field->bf_size &&
    isalnum(field->buffer[field->cursor_pos]))
        field->cursor_pos++;
    return 0;
}

int ctrl_left_arrow(textfield_t *field, UNUSED char seq[], UNUSED head_t *head)
{
    while (field->cursor_pos > 0 && !isalnum(field->buffer[field->cursor_pos]))
        field->cursor_pos--;
    while (field->cursor_pos > 0 && isalnum(field->buffer[field->cursor_pos]))
        field->cursor_pos--;
    return 0;
}
