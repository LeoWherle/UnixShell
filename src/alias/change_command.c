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

int get_alias_index(char *alias, alias_t **aliases)
{
    int i = 0;

    while (aliases[i]) {
        if (strcmp(aliases[i]->alias, alias) == 0)
            return i;
        i++;
    }
    return -1;
}

char *get_full_command(char **command)
{
    char *full_command = NULL;
    int len = 0;
    int in = 0;

    for (int i = 0; command[i]; i++) {
        len += strlen(command[i]);
        len++;
    }
    full_command = malloc(sizeof(char) * (len + 1));
    strcpy(full_command, "");
    for (in = 0; command[in]; in++) {
        my_strcat(full_command, command[in]);
        my_strcat(full_command, " ");
    }
    full_command[len + 1] = '\0';
    return full_command;
}

char *change_command(char *command, alias_t **aliases)
{
    int index = 0;
    char **command_split = my_str_to_word_array(command, ' ');

    if (!command_split)
        return NULL;
    for (int i = 0; command_split[i]; i++) {
        index = get_alias_index(command_split[i], aliases);
        if (index != -1) {
            command_split[i] = strdup(aliases[index]->command);
        }
    }
    return get_full_command(command_split);
}
