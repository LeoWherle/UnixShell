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
            printf("%s\t(%s)\n", data->alias, data->command);
            return 0;
        }
        ali = ali->next;
    }
    printf("alias %s not found\n", command[1]);
    return 1;
}

static int print_alias(char **command, head_t *head, int *ret)
{
    node_t *ali = head->alias->head;
    alias_t *data = NULL;

    if (!command[1]) {
        while (ali) {
            data = ali->data;
            printf("%s\t(%s)\n", data->alias, data->command);
            ali = ali->next;
        }
    } else {
        *ret = print_specific_alias(command, head);
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
int alias_builtin(char **command, head_t *head, int *ret)
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
    return *ret = print_alias(command, head, ret);
}
