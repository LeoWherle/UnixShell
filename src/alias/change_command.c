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

static char *get_alias(char *command_part, list_t *aliases)
{
    char *command = NULL;
    node_t *ali = aliases->head;
    alias_t *data = NULL;

    while (ali) {
        data = ali->data;
        if (strcmp(data->alias, command_part) == 0) {
            free(command_part);
            command = strdup(data->command);
            ASSERT_MALLOC(command, NULL);
            return command;
        }
        ali = ali->next;
    }
    return command_part;
}

static char *get_env(char *command_part, env_t *env)
{
    char *command = NULL;
    char *var_name = NULL;
    env_t *env_var = NULL;

    if (command_part[0] == '$') {
        env_var = find_env(env, command_part + 1);
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
        command_split[i] = get_env(command_split[i], head->first);
        ASSERT_PTR(command_split[i], NULL);
    }
    return get_full_command(command_split);
}
