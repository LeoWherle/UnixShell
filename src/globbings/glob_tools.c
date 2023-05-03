/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** Build the list of matches for a globbing pattern
*/

#include <string.h>
#include <stdlib.h>
#include "globber.h"
#include "clist.h"

list_t *parse_pattern(const char *pattern)
{
    list_t *list = NULL;
    char *tmp = NULL;
    int i = 0;
    int k = 0;

    list = list_init();
    while (pattern[i] != '\0') {
        if (pattern[i] == '/' && (i != 0 && pattern[i - 1] != '\\')) {
            tmp = strndup(pattern + k, i);
            k = i + 1;
            list->interface->append(list, tmp);
        }
        i++;
    }
    return list;
}

static int calc_str_list_len(list_t *list)
{
    int len = 0;
    node_t *node = list->head;

    while (node) {
        len += strlen(node->data);
        node = node->next;
    }
    return len;
}

char *str_from_list(list_t *list)
{
    char *str = NULL;
    char *tmp = NULL;
    int i = 0;

    str = malloc(calc_str_list_len(list) + 1);
    while (list->size > 0) {
        tmp = list->interface->popf(list);
        for (int j = 0; tmp[j] != '\0'; j++, i++) {
            str[i] = tmp[j];
        }
        free(tmp);
    }
    str[i] = '\0';
    return str;
}

void add_prefix_to_list(list_t *list, const char *prefix)
{
    node_t *node = list->head;
    char *tmp = NULL;

    while (node) {
        tmp = node->data;
        node->data = malloc(strlen(prefix) + strlen(tmp) + 1);
        strcpy(node->data, prefix);
        strcat(node->data, tmp);
        free(tmp);
        node = node->next;
    }
}
