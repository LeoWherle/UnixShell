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

static char *exec_special_echo(env_t *env, char *var_name, int ret)
{
    env_t *temp = env;

    if (var_name[0] == '\0') {
        printf("$");
        return (NULL);
    }
    if (var_name[0] == '?') {
        printf("%d", ret);
        return (NULL);
    }
    while (temp->next != NULL) {
        if (my_strncmp(temp->line, var_name, my_strlen(var_name) - 1) == 0)
            return (temp->line + my_strlen(var_name) + 1);
        temp = temp->next;
    }
    return (NULL);
}

int my_echo(char **command_line, head_t *head, int *ret)
{
    char *text = NULL;
    int i = 1;

    while (command_line[i] != NULL) {
        if (command_line[i][0] != '-') {
            text = command_line[i];
            break;
        }
        i++;
    }
    if (text != NULL && text[0] == '$')
        text = exec_special_echo(head->first, text + 1, *ret);
    if (text == NULL) {
        printf("\n");
        return *ret = 0;
    }
    printf("%s\n", text);
    return *ret = 0;
}
