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

int get_nb_alias(void)
{
    FILE *fd = fopen(".42rc", "r");
    char *line = NULL;
    size_t size = 0;
    int nb_alias = 0;

    if (!fd)
        return 0;
    while (getline(&line, &size, fd) != -1) {
        if (line[0] == 'a' && line[1] == 'l' && line[2] == 'i' &&
            line[3] == 'a' && line[4] == 's')
            nb_alias++;
    }
    return nb_alias;
}

void parse_alias(char *line, alias_t *alias)
{
    char **alias_split = my_str_to_word_array(line, ':');
    int len = matrix_len(alias_split);

    if (len != 3)
        return;
    alias->alias = strdup(alias_split[1]);
    if (alias_split[2][strlen(alias_split[2]) - 1] == '\n')
        alias_split[2][strlen(alias_split[2]) - 1] = '\0';
    alias->command = strdup(alias_split[2]);
}

alias_t **get_alias_list(void)
{
    int nb_alias = get_nb_alias();
    char *line = NULL;
    size_t size = 0;
    int in = 0;
    FILE *fd = fopen(".42rc", "r");
    alias_t **aliases = malloc(sizeof(alias_t *) * (nb_alias + 1));

    if (!fd)
        return NULL;
    while (getline(&line, &size, fd) != -1) {
        if (line[0] == 'a' && line[1] == 'l' && line[2] == 'i' &&
            line[3] == 'a' && line[4] == 's') {
            aliases[in] = malloc(sizeof(alias_t));
            parse_alias(line, aliases[in]);
            in++;
        }
    }
    aliases[in] = NULL;
    return aliases;
}
