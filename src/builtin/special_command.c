/*
** EPITECH PROJECT, 2023
** special_command
** File description:
** rebuilded function
*/

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "mysh.h"

static int env_error(int len, head_t *head)
{
    if (len > 3) {
        write(2, "setenv: Too many arguments.\n", 28);
        return 1;
    }
    for (env_t *env = head->first; env->line != NULL; env = env->next) {
        write(1, env->line, my_strlen(env->line));
        write(1, "\n", 1);
    }
    return 0;
}

static bool conformity(char *var)
{
    if ((var[0] < 'a' || var[0] > 'z') &&
        (var[0] < 'A' || var[0] > 'Z')) {
        write(2, "setenv: Variable name must begin with a letter.\n", 48);
        return true;
    }
    if (!my_str_isalphanum(var)) {
        write(2, "setenv: Variable name"
                " must contain alphanumeric characters.\n", 60);
        return true;
    }
    return false;
}

void replace_var(char *new, head_t *head)
{
    char *path = NULL;

    if (my_strncmp(new, "PATH=", 4) == 0) {
        if (head->path)
            free_matrix(head->path);
        head->path = find_path(head->first);
    }
    if (my_strncmp(new, "HOME=", 4) == 0) {
        if (head->home)
            free(head->home);
        if (my_strcmp(new, "HOME=") != 0) {
            head->home = malloc((my_strlen(&new[5]) + 1) * sizeof(char));
            my_strcpy(head->home, &new[5]);
        } else {
            path = getcwd(path, 0);
            head->home = malloc((my_strlen(path) + 1) * sizeof(char));
            my_strcpy(head->home, path);
        }
    }
}

int my_setenv(char **c, head_t *head, int *ret)
{
    env_t *t = NULL;
    if (matrix_len(c) > 3 || matrix_len(c) == 1)
        return *ret = env_error(matrix_len(c), head);
    if (conformity(c[1]))
        return *ret = 1;
    t = find_env(head->first, c[1]);
    if (t->line != NULL)
        free(t->line);
    else {
        head->size++,
        t->next = add_env(NULL);
    }
    t->line = malloc((my_strlen(c[1]) + my_strlen(c[2]) + 4) * sizeof(char));
    if (!t->line || !t->next)
        return *ret = -2;
    my_strcpy(t->line, c[1]);
    my_strcat(t->line, "=");
    my_strcat(t->line, c[2]);
    replace_var(t->line, head);
    return *ret = 0;
}

int my_unsetenv(char **c, head_t *head, int *ret)
{
    env_t *t = NULL;
    env_t *p = NULL;

    if (matrix_len(c) == 1)
        return *ret = write(2, "unsetenv: Too few arguments.\n", 29) / 29;
    for (int i = 1; c[i] != NULL; i++) {
        t = find_env(head->first, c[i]);
        if (t->line == NULL)
            continue;
        head->size--;
        if (t == head->first) {
            head->first = t->next;
            p = t;
        }
        for (p = head->first; p->next != t && p != t; p = p->next);
        p->next = t->next;
        free(t->line);
        free(t);
    }
    return 0;
}
