/*
** EPITECH PROJECT, 2023
** special_command
** File description:
** rebuilded function
*/

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include "mysh.h"

static int handle_error(char *shit, head_t *head, int *r)
{
    int i = 0;

    if (shit[0] != '-' && (shit[0] < '0' || shit[0] > '9')) {
        write(2, "exit: Expression Syntax.\n", 25);
        *r = 1;
        return 1;
    }
    for (i = 1; shit[i] >= '0' && shit[i] <= '9'; i++);
    if ((shit[i] < '0' || shit[i] > '9') && shit[i] != '\0') {
        write(2, "exit: Badly formed number.\n", 27);
        *r = 1;
        return 1;
    } else if (shit[i] == '\0' && (shit[i - 1] < '0' || shit[i - 1] > '9')) {
        write(2, "exit: Expression Syntax.\n", 25);
        *r = 1;
        return 1;
    }
    *r = my_getnbr(shit);
    head->keep = false;
    return 0;
}

int my_exit(char **command_line, head_t *head)
{
    int len = 0;
    int r = 0;

    len = matrix_len(command_line);
    if (len == 1) {
        head->keep = false;
        return head->lr;
    }
    if (len == 2)
        handle_error(command_line[1], head, &r);
    if (len > 2) {
        if (handle_error(command_line[1], head, &r) == 0)
            write(2, "exit: Expression Syntax.\n", 25);
        return 1;
    }
    return r;
}

int my_env(char **command_line, head_t *head)
{
    struct stat extract = {0};
    if (matrix_len(command_line) == 1) {
        for (env_t *env = head->first; env->line != NULL; env = env->next) {
            write(1, env->line, my_strlen(env->line));
            write(1, "\n", 1);
        }
        return 0;
    } else {
        write(2, "env : '", 7);
        write(2, command_line[1], my_strlen(command_line[1]));
        if (lstat(command_line[1], &extract) == -1) {
            write(2, "': No such file or directory\n", 29);
            return 127;
        } if (S_ISREG(extract.st_mode)) {
            write(2, "': No such file or directory\n", 29);
            return 127;
        }
        write(2, "' Permission denied\n", 20);
        return 126;
    }
}

static int print_echo(char *text, char **command_line, int i)
{
    int index = 0;

    if (text == NULL) {
        write(1, "\n", 1);
        return 0;
    }
    for (index = 0; text[index] != '\0'; index++) {
        if ((text[index] != '"' && text[index] != '\'' && text[index] != '\\')
        || text[index - 1] == '\\')
            write(1, &text[index], 1);
    }
    if (command_line[i + 1] != NULL && command_line[i + 1][0] != '-')
        write(1, " ", 1);
    return 0;
}

int my_echo(char **command_line, UNUSED head_t *head)
{
    char *text = NULL;
    int i = 1;
    int line_break = 1;

    while (command_line[i] != NULL) {
        if (my_strcmp(command_line[i], "-n") == 0)
            line_break = 0;
        if (command_line[i][0] != '-') {
            text = command_line[i];
            print_echo(text, command_line, i);
        }
        i++;
    }
    if (line_break == 1)
        write(1, "\n", 1);
    return 0;
}
