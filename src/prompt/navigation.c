/*
** EPITECH PROJECT, 2023
** 42sh [WSL: fedora]
** File description:
** navigation
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include "errorh.h"
#include "prompt.h"

void create_new_termios(struct termios *old, struct termios *new)
{
    tcgetattr(STDIN_FILENO, old);
    *new = *old;
    new->c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, new);
}

int read_input(char **buffer)
{
    struct termios old;
    struct termios new;
    textfield_t textfield = {.bf_size = 0, .cursor_pos = 0};

    create_new_termios(&old, &new);
    terminal_loop(&textfield);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &new);
    if (textfield.buffer != NULL) {
        *buffer = strdup(textfield.buffer);
        ASSERT_PTR(textfield.buffer, EOF);
        free(textfield.buffer);
    }
    return (textfield.bf_size);
}
