/*
** EPITECH PROJECT, 2023
** 42sh [WSL: fedora]
** File description:
** prompt_ansi
*/

#include <string.h>
#include <stdio.h>
#include "prompt.h"

void escape(textfield_t *field)
{
    printf("\033");
    field->bf_size = strlen(field->buffer);
    return;
}
