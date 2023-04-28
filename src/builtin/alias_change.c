/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** change alias list
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fcntl.h"
#include "rcfile.h"
#include "mysh.h"

static char *cat_command(char **builtin_split)
{
    char *command = NULL;
    int len = 0;

    for (int i = 2; builtin_split[i]; i++) {
        len += strlen(builtin_split[i]);
        len++;
    }
    command = malloc(sizeof(char) * (len + 1));
    ASSERT_MALLOC(command, NULL);
    strcpy(command, "");
    for (int i = 2; builtin_split[i]; i++) {
        my_strcat(command, builtin_split[i]);
        my_strcat(command, " ");
    }
    command[len - 1] = '\0';
    printf("command: %s\n", command);
    return command;
}

static int create_alias(char **command, head_t *head)
{
    alias_t *new = NULL;

    new = malloc(sizeof(alias_t));
    ASSERT_MALLOC(new, 84);
    new->alias = strdup(command[1]);
    ASSERT_PTR(new->alias, 84);
    new->command = cat_command(command);
    ASSERT_PTR(new->command, 84);
    node_append(head->alias, new);
    return 0;
}

int change_alias(char **command, head_t *head)
{
    node_t *ali = head->alias->head;
    alias_t *data = NULL;

    while (ali) {
        data = ali->data;
        if (strcmp(data->alias, command[1]) == 0) {
            free(data->command);
            data->command = cat_command(command);
            ASSERT_PTR(data->command, 84);
            return 0;
        }
        ali = ali->next;
    }
    return create_alias(command, head);
}
