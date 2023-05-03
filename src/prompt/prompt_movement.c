/*
** EPITECH PROJECT, 2023
** 42sh [WSL: fedora]
** File description:
** prompt_movement
*/

#include <sys/types.h>
#include <stdio.h>
#include "prompt.h"

chartype_t g_chartypes[] = {
    {'\n', newline},
    {'\t', tabulation},
    {27, escape},
    {127, backspace},
    {'\b', backspace},
    {'\0', standart_char}
};

void handle_chartype(textfield_t *field, char c)
{
    unsigned int i = 0;

    for (i = 0; i < TAB_SIZE(g_chartypes) ; i++) {
        if (c == g_chartypes[i].type)
            g_chartypes[i].handler(field);
        if (i == TAB_SIZE(g_chartypes) - 1)
            g_chartypes[i].handler(field);
    }
}

void terminal_loop(textfield_t *field)
{
    int c = -1;

    c = getchar();
    while (c != EOF || c != '\n') {
        handle_chartype(field, c);
        c = getchar();
    }
    if (c == EOF) {
        field->bf_size = EOF;
    }
    return;
}
