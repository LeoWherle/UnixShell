/*
** EPITECH PROJECT, 2023
** env
** File description:
** env related function
*/

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include "mysh.h"

env_t *find_env(env_t *env, char *to_find)
{
    int len = 0;

    len = my_strlen(to_find) - 1;
    for (env = env; env->line != NULL; env = env->next)
        if (my_strncmp(env->line, to_find, len) == 0)
            return env;
    return env;
}

env_t *add_env(char const *txt)
{
    env_t *node = NULL;

    node = malloc(sizeof(env_t));
    if (!node)
        return NULL;
    if (txt != NULL) {
        node->line = malloc((my_strlen(txt) + 2) * sizeof(char));
        if (!node->line) {
            free(node);
            return NULL;
        }
        my_strcpy(node->line, txt);
    } else
        node->line = NULL;
    return node;
}

static int rec(env_t *env, head_t *head, char * const *e, int i)
{
    int r = 0;
    env->next = add_env(e[i]);
    if (!env->next)
        return -1;
    if (!env->next->line)
        return i;
    r = rec(env->next, head, e, i + 1);
    if (r < 1) {
        free(env->line);
        free(env);
    }
    return r;
}

void make_env(char * const *e, head_t *head)
{
    env_t *a = NULL;
    env_t *hold = NULL;
    a = add_env(e[0]);
    head->first = a;
    head->keep = true;
    head->size = rec(head->first, head, e, 1) + 1;
    head->pwd = find_env(head->first, "PWD");
    if (!head->pwd->line || head->pwd->line[4] == '\0')
        new_pwd(head->pwd, head);
    hold = find_env(head->first, "OLDPWD");
    head->oldpwd = NULL;
    if (hold->line)
        head->oldpwd = hold;
    hold = find_env(head->first, "HOME");
    head->home = NULL;
    if (hold->line) {
        head->home = malloc((my_strlen(&hold->line[5]) + 1) * sizeof(char));
        my_strcpy(head->home, &hold->line[5]);
    }
}

void free_env(env_t *env)
{
    if (env->line != NULL) {
        free_env(env->next);
        free(env->line);
    }
    free(env);
}
