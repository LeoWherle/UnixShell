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
#include "42rc.h"
#include "mysh.h"

int get_nb_alias(void)
{
    int fd = open(".42rc", O_RDONLY);
    char *line = NULL;
    size_t size = 0;
    int nb_alias = 0;

    if (fd == -1)
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
    alias->command = strdup(alias_split[2]);
}

alias_t **get_alias_list(void)
{
    int nb_alias = get_nb_alias();
    char *line = NULL;
    size_t size = 0;
    int in = 0;
    int fd = open(".42rc", O_RDONLY);
    alias_t **aliases = malloc(sizeof(alias_t *) * (nb_alias + 1));

    if (fd == -1)
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

char *change_command(char *command, alias_t **aliases)
{
    int i = 0;
    char **command_split = my_str_to_word_array(command, ' ');

    if (!aliases || !command_split)
        return NULL;
    
    return command;
}