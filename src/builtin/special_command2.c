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

static int solve_this_shit(char *shit, head_t *head, int *r)
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

int my_exit(char **command_line, head_t *head, int *r)
{
    int len = 0;

    len = matrix_len(command_line);
    if (len == 1) {
        head->keep = false;
        *r = head->lr;
    }
    if (len == 2)
        solve_this_shit(command_line[1], head, r);
    if (len > 2) {
        if (solve_this_shit(command_line[1], head, r) == 0)
            write(2, "exit: Expression Syntax.\n", 25);
        *r = 1;
    }
    return 1;
}

int my_env(char **command_line, head_t *head, int *ret)
{
    struct stat extract = {0};
    if (matrix_len(command_line) == 1) {
        for (env_t *env = head->first; env->line != NULL; env = env->next) {
            write(1, env->line, my_strlen(env->line));
            write(1, "\n", 1);
        }
        return *ret = 0;
    } else {
        write(2, "env : '", 7);
        write(2, command_line[1], my_strlen(command_line[1]));
        if (lstat(command_line[1], &extract) == -1) {
            write(2, "': No such file or directory\n", 29);
            return *ret = 127;
        } if (S_ISREG(extract.st_mode)) {
            write(2, "': No such file or directory\n", 29);
            return *ret = 127;
        }
        write(2, "' Permission denied\n", 20);
        return *ret = 126;
    }
}
