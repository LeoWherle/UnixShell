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
#include "errorh.h"
#include "clist.h"
#include "mysh.h"

static int parse_alias(char *line, alias_t *alias)
{
    char **alias_split = my_str_to_word_array(line, ':');
    int len = matrix_len(alias_split);
    int command_len = 0;

    if (len != 3)
        return 0;
    alias->alias = strdup(alias_split[1]);
    ASSERT_MALLOC(alias->alias, -1);
    command_len = strlen(alias_split[2]);
    if (alias_split[2][command_len - 1] == '\n')
        alias_split[2][command_len - 1] = '\0';
    alias->command = strdup(alias_split[2]);
    ASSERT_MALLOC(alias->command, -1);
    free_matrix(alias_split);
    return 1;
}

static list_t *create_alias_node(char *line, list_t *aliases)
{
    alias_t *alias = malloc(sizeof(alias_t));
    int ret = 0;

    ASSERT_MALLOC(alias, NULL);
    ret = parse_alias(line, alias);
    if (ret == -1)
        return NULL;
    if (ret == 0)
        return aliases;
    if (node_append(aliases, alias))
        return NULL;
    return aliases;
}

list_t *get_alias_list(void)
{
    char *line = NULL;
    size_t size = 0;
    FILE *fd = fopen(".42rc", "r");
    list_t *aliases = list_init();

    if (!fd || !aliases)
        return NULL;
    while (getline(&line, &size, fd) != -1) {
        if (strncmp(line, "alias", 5) == 0) {
            aliases = create_alias_node(line, aliases);
            ASSERT_PTR(aliases, NULL);
        }
    }
    fclose(fd);
    free(line);
    return aliases;
}

void free_alias(void *void_alias)
{
    alias_t *alias = void_alias;

    free(alias->alias);
    free(alias->command);
    free(alias);
}

char *get_alias(char *command_part, list_t *aliases)
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
