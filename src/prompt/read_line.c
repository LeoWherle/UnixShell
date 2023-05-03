/*
** EPITECH PROJECT, 2023
** 42sh [WSL: fedora]
** File description:
** file
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include "errorh.h"
#include "prompt.h"

static void enable_raw_mode(struct termios *orig_termios)
{
    struct termios raw;

    tcgetattr(STDIN_FILENO, orig_termios);
    raw = *orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

static void disable_raw_mode(struct termios *orig_termios)
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, orig_termios);
}

static void print_state(textfield_t *field)
{
    if (isatty(STDIN_FILENO)) {
        printf("\033[2K\r");
        int lentt = print_shell();
        printf("%s", field->buffer);
        printf("\033[%dG", lentt + field->cursor_pos + 1);
        fflush(stdout);
    }
}

int read_line(char **output)
{
    struct termios orig_termios;
    textfield_t field = {.bf_size = 0, .cursor_pos = 0};
    char c = 0;

    enable_raw_mode(&orig_termios);
    while (1) {
        c = getchar();
        if (c == EOF || c == '\4') {
            disable_raw_mode(&orig_termios);
            return EOF;
        }
        if (handle_char(&field, c)) {
            break;
        }
        print_state(&field);
    }
    *output = strdup(field.buffer);
    disable_raw_mode(&orig_termios);
    return strlen(field.buffer);
}
