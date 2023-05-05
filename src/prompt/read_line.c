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
    int prompt_len = 0;

    if (isatty(STDIN_FILENO)) {
        printf("\033[2K\r");
        prompt_len = print_shell();
        printf("%s", field->buffer);
        printf("\033[%dG", prompt_len + field->cursor_pos + 1);
        fflush(stdout);
    }
}

int terminal_loop(struct termios *orig_termios, textfield_t *field)
{
    char c = 0;

    c = getchar();
    while (c != EOF && c != '\4') {
        if (handle_char(field, c)) {
            break;
        }
        print_state(field);
        c = getchar();
    }
    disable_raw_mode(orig_termios);
    if (c == EOF || c == '\4') {
        return EOF;
    }
    return field->bf_size;
}

int read_line(char **output)
{
    struct termios orig_termios;
    textfield_t field = {.bf_size = 0, .cursor_pos = 0};
    int ret = 0;

    size_t size = 0;
    memset(field.buffer, 0, sizeof(field.buffer));
    if (!isatty(STDIN_FILENO)) {
        return getline(output, &size, stdin);
    } else {
        enable_raw_mode(&orig_termios);
        ret = terminal_loop(&orig_termios, &field);
        *output = strdup(field.buffer);
    }
    return ret;
}
