#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include "prompt.h"
#include "errorh.h"

#define MAX_INPUT_SIZE 1024

// Function prototypes
void enable_raw_mode(struct termios *orig_termios);
void disable_raw_mode(struct termios *orig_termios);
int print_shell();

void enable_raw_mode(struct termios *orig_termios)
{
    struct termios raw;

    tcgetattr(STDIN_FILENO, orig_termios);
    raw = *orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disable_raw_mode(struct termios *orig_termios)
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, orig_termios);
}

int enter_key(UNUSED textfield_t *field)
{
    putchar('\n');
    return 1;
}

int tab_key(UNUSED textfield_t *field)
{
    return 0;
}

int back_key(textfield_t *field)
{
    if (field->cursor_pos > 0) {
        memmove(field->buffer + field->cursor_pos - 1,
            field->buffer + field->cursor_pos,
            strlen(field->buffer) - field->cursor_pos + 1);
        (field->cursor_pos)--;
    }
    return 0;
}

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

int delete_key(textfield_t *field, char seq[])
{
    if (seq[1] == '~') {
        if (field->cursor_pos < strlen(field->buffer)) {
            memmove(field->buffer + field->cursor_pos,
                field->buffer + field->cursor_pos + 1,
                strlen(field->buffer) - field->cursor_pos);
        }
    }
    return 0;
}

// ANSI escape sequences
static const escchartype_t escapechars[] = {
    {'A', up_arrow},
    {'B', down_arrow},
    {'C', right_arrow},
    {'D', left_arrow},
    {'3', delete_key},
};

int esc_key(textfield_t *field)
{
    char seq[3];

    if (getchar() == '[') {
        seq[0] = getchar();
        if (seq[0] >= '0' && seq[0] <= '9') {
            seq[1] = getchar();
        }
    }
    for (unsigned int i = 0; i < TAB_SIZE(escapechars); i++) {
        if (seq[0] == escapechars[i].type) {
            return escapechars[i].handler(field, seq);
        }
    }
    return 0;
}

// characters that require special handling (including escape sequences 27)
static const chartype_t specialchars[] = {
    {'\n', enter_key},
    {'\t', tab_key},
    {127, back_key},
    {27, esc_key},
};

int handle_char(textfield_t *field, char c)
{
    for (unsigned int i = 0; i < TAB_SIZE(specialchars); i++) {
        if (c == specialchars[i].type) {
            return specialchars[i].handler(field);
        }
    }
    if (field->cursor_pos < MAX_INPUT_SIZE - 1) {
        memmove(field->buffer + field->cursor_pos + 1,
            field->buffer + field->cursor_pos,
            strlen(field->buffer) - field->cursor_pos);
        field->buffer[field->cursor_pos] = c;
        field->cursor_pos++;
    }
    return 0;
}

void print_state(textfield_t *field)
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
