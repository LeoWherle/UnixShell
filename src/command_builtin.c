/*
** EPITECH PROJECT, 2023
** 42sh [WSL: fedora]
** File description:
** command_builtin
*/

#include <stdbool.h>
#include "mysh.h"

static const builtin_cmd_t builtin_commands[] = {
    {"cd", &change_dir},
    {"exit", &my_exit},
    {"setenv", &my_setenv},
    {"unsetenv", &my_unsetenv},
    {"env", &my_env},
    {"alias", &alias_builtin},
    {"echo", &my_echo},
};

bool exec_special_case(char **command_line, head_t *head, int *r)
{
    int cmd_amount = sizeof(builtin_commands) / sizeof(builtin_cmd_t);

    for (int it = 0; it < cmd_amount; it++) {
        if (my_strcmp(command_line[0], builtin_commands[it].name) == 0) {
            *r = builtin_commands[it].func(command_line, head, r);
            return true;
        }
    }
    return false;
}
