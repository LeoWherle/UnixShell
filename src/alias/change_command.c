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
#include "rcfile.h"
#include "mysh.h"

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
            command = strdup(data->command);
            ASSERT_MALLOC(command, NULL);
            return command;
        }
        ali = ali->next;
    }
    return command_part;
}

char *change_command(char *command, list_t *aliases)
{
    char **command_split = my_str_to_word_array(command, ' ');

    free(command);
    ASSERT_MALLOC(command_split, NULL);
    for (int i = 0; command_split[i]; i++) {
        if (i != 0 && strcmp(command_split[i - 1], "alias") == 0)
            continue;
        command_split[i] = get_alias(command_split[i], aliases);
        ASSERT_MALLOC(command_split[i], NULL);
    }
    return get_full_command(command_split);
}
