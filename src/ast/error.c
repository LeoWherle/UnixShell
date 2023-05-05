/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** AST error
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "ast.h"
#include "errorh.h"
#include "mysh.h"

bool check_qm(char *line)
{
    int qm = 0;

    for (int i = 0; line[i]; i++) {
        if (line[i] == '?')
            qm++;
    }
    if (qm > 1)
        return false;
    return true;
}

int check_env_case(env_t *env, char *arg)
{
    env_t *env = NULL;

    if (arg[0] == '$') {
        env = get_env(arg + 1);
        if (!env->line) {
            printf("%s: Undefined variable.\n", arg + 1);
            return 1;
        }
        if (!check_qm(env->line)) {
            printf("No mtach.\n");
            return 1;
        }
    }
    return 0;
}

int check_args(ast_t *node)
{
    char **args = node->data;
    env_t *env = NULL;

    for (int i = 0; args[i]; i++) {
        if (check_env_case(env, args[i]))
            return 1;
    }
    return 0;
}
