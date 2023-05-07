/*
** EPITECH PROJECT, 2023
** 42sh [WSL: fedora]
** File description:
** char_handle
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "errorh.h"
#include "prompt.h"

// characters that require special handling (including escape sequences 27)
static const chartype_t specialchars[] = {
    {'\n', enter_key},
    {'\t', tab_key},
    {'\x7F', backspace_key},
    {'\033', esc_key},
};

int handle_char(textfield_t *field, char c, head_t *head)
{
    for (unsigned int i = 0; i < TAB_SIZE(specialchars); i++) {
        if (c == specialchars[i].type) {
            return specialchars[i].handler(field, head);
        }
    }
    if (field->cursor_pos < MAX_INPUTLINE - 1) {
        memmove(field->buffer + field->cursor_pos + 1,
            field->buffer + field->cursor_pos,
            field->bf_size - field->cursor_pos);
        field->buffer[field->cursor_pos] = c;
        field->cursor_pos++;
        field->bf_size++;
    }
    if (field->cursor_pos == MAX_INPUTLINE - 1) {
        return 1;
    }
    return 0;
}
