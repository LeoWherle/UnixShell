/*
** EPITECH PROJECT, 2023
** Alias
** File description:
** builtin
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fcntl.h"
#include "rcfile.h"
#include "mysh.h"

static int print_specific_alias(char **command, head_t *head)
{
    node_t *ali = head->alias->head;
    alias_t *data = NULL;

    while (ali) {
        data = ali->data;
        if (strcmp(data->alias, command[1]) == 0) {
            printf("%s\t%s\n", data->alias, data->command);
            return 0;
        }
        ali = ali->next;
    }
    return 0;
}

static void sort_conditon(alias_t **alias_list, int i, int j)
{
    alias_t *tmp = NULL;

    if (strcmp(alias_list[i]->alias, alias_list[j]->alias) > 0) {
        tmp = alias_list[i];
        alias_list[i] = alias_list[j];
        alias_list[j] = tmp;
    }
}

static void sort_alias(alias_t **alias_list)
{
    int i = 0;
    int j = 0;

    for (i = 0; alias_list[i]; i++) {
        for (j = i + 1; alias_list[j]; j++) {
            sort_conditon(alias_list, i, j);
        }
    }
}

static int print_alias(char **command, head_t *head)
{
    alias_t *data = NULL;
    alias_t **alias_list = NULL;

    if (!command[1]) {
        alias_list = (alias_t **)array_build(head->alias);
        ASSERT_PTR(alias_list, 84);
        sort_alias(alias_list);
        for (int i = 0; alias_list[i]; i++) {
            data = alias_list[i];
            printf("%s\t%s\n", data->alias, data->command);
        }
        free(alias_list);
    } else {
        return print_specific_alias(command, head);
    }
    return 0;
}

/**
 * @brief alias builtin
 * if no args, print all alias
 * if 1 arg, print arg alias
 * if 2 or more args, create alias
 * return 0 if success, 1 if error
 *
 * @param command
 * @param head
 * @param ret
 * @return int
 */
int alias_builtin(char **command, head_t *head)
{
    int len = matrix_len(command);

    if (len >= 3) {
        if (strcmp(command[1], "alias") == 0) {
            printf("alias: Too dangerous to alias that.\n");
            return 1;
        }
        if (change_alias(command, head) == 84)
            return 84;
        return 0;
    }
    return print_alias(command, head);
}
