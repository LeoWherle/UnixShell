/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** alias
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fcntl.h"
#include "mysh.h"
#include "rcfile.h"

static char *get_full_command(char **command)
{
    char *full_command = NULL;
    int len = 0;
    int in = 0;

    for (int i = 0; command[i]; i++) {
        len += strlen(command[i]);
        len++;
    }
    full_command = malloc(sizeof(char) * (len + 1));
    ASSERT_MALLOC(full_command, NULL);
    strcpy(full_command, "");
    for (in = 0; command[in]; in++) {
        my_strcat(full_command, command[in]);
        my_strcat(full_command, " ");
    }
    full_command[len] = '\0';
    free_matrix(command);
    return full_command;
}

static char *get_return_value(char *command_part, head_t *head)
{
    char *last_ret = NULL;
    int nb_qm = 0;

    for (int i = 0; command_part[i]; i++)
        if (command_part[i] == '?')
            nb_qm++;
    if (command_part[1] == '?' && nb_qm == 1) {
        last_ret = malloc(10 * sizeof(char));
        ASSERT_MALLOC(last_ret, NULL);
        sprintf(last_ret, "%d", head->lr);
        free(command_part);
        return last_ret;
    }
    return command_part;
}

static char *special_env(char *command_part, head_t *head)
{
    char *special_env = NULL;
    int i = 0;

    if (command_part[1] == '0') {
        special_env = malloc(strlen(command_part) + 5 * sizeof(char));
        ASSERT_MALLOC(special_env, NULL);
        strcpy(special_env, "42sh");
        for (i = 1; command_part[i] == '0'; i++);
        if (command_part[i] != '\0')
            strcat(special_env, command_part + 2);
        free(command_part);
        return special_env;
    }
    special_env = get_return_value(command_part, head);
    ASSERT_PTR(special_env, NULL);
    return special_env;
}

static char *get_env(char *command_part, head_t *head)
{
    char *command = NULL;
    char *var_name = NULL;
    env_t *env_var = NULL;

    if (command_part[0] == '$') {
        if (command_part[1] == '?' || command_part[1] == '0')
            return special_env(command_part, head);
        env_var = find_env(head->first, command_part + 1);
        if (env_var->line) {
            var_name = command_part + 1;
            command = strdup(env_var->line + strlen(var_name) + 1);
            ASSERT_MALLOC(command, NULL);
            free(command_part);
            return command;
        }
    }
    return command_part;
}

char *change_command(char *command, head_t *head)
{
    char **command_split = my_str_to_word_array(command, ' ');

    free(command);
    ASSERT_MALLOC(command_split, NULL);
    for (int i = 0; command_split[i]; i++) {
        if (i != 0 && strcmp(command_split[i - 1], "alias") == 0)
            continue;
        command_split[i] = get_alias(command_split[i], head->alias);
        ASSERT_PTR(command_split[i], NULL);
        command_split[i] = get_env(command_split[i], head);
        ASSERT_PTR(command_split[i], NULL);
    }
    return get_full_command(command_split);
}
