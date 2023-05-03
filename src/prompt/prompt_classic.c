/*
** EPITECH PROJECT, 2023
** 42sh [WSL: fedora]
** File description:
** prompt_classic
*/

#include <string.h>
#include <stdio.h>
#include "prompt.h"

void newline(textfield_t *field)
{
    printf("\n");
    field->bf_size = strlen(field->buffer);
    return;
}

void tabulation(textfield_t *field)
{
    printf("\t");
    field->bf_size = strlen(field->buffer);
    return;
}

void backspace(textfield_t *field)
{
    if (field->cursor_pos > 0) {
        printf("\b \b");
        field->buffer[field->cursor_pos - 1] = '\0';
        field->cursor_pos--;
    }
    field->bf_size = strlen(field->buffer);
    return;
}

void standart_char(textfield_t *field)
{
    printf("%c", field->buffer[field->cursor_pos]);
    field->cursor_pos++;
    field->bf_size = strlen(field->buffer);
    return;
}
