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

static int calc_str_list_len(list_t *list)
{
    int len = 0;
    node_t *node = list->head;

    while (node) {
        if (node->data)
            len += strlen(node->data) + 1;
        node = node->next;
    }
    return len;
}

char *str_from_list(list_t *list)
{
    char *str = NULL;
    char *tmp = NULL;
    int i = 0;
    int j = 0;

    if (!list || list->size == 0) {
        return NULL;
    }
    str = malloc(calc_str_list_len(list));
    while (list->size > 0) {
        tmp = list->interface->popf(list);
        if (!tmp)
            continue;
        for (j = 0; tmp[j] != '\0'; j++, i++)
            str[i] = tmp[j];
        str[i++] = ' ';
        free(tmp);
    }
    str[--i] = '\0';
    return str;
}

void add_prefix_to_list(list_t *list, const char *prefix)
{
    node_t *node = NULL;

    if (!list || list->size == 0 || !prefix || prefix[0] == '\0') {
        return;
    }
    node = list->head;
    while (node) {
        add_prefix_to_str((char **)&node->data, prefix);
        node = node->next;
    }
}

void insert_list_in_tab(char ***tab, list_t *list, int i)
{
    int size = 0;
    int lsize = list->size;
    char **tmp = *tab;

    for (; tmp[size]; size++);
    tmp = malloc(sizeof(char *) * (size + lsize + 1));
    for (int j = 0; j < i; j++) {
        tmp[j] = (*tab)[j];
    }
    for (int j = 0; j < lsize; j++) {
        tmp[i + j] = list->interface->popf(list);
    }
    for (int j = i; tab[j + 1]; j++) {
        tmp[j + lsize] = (*tab)[j + 1];
    }
    tmp[size + lsize - 1] = NULL;
    *tab = tmp;
}

char **list_to_tab(list_t *list)
{
    char **tab = NULL;
    node_t *node = list->head;
    int i = 0;

    tab = malloc(sizeof(char *) * (list->size + 1));
    while (node) {
        tab[i] = strdup(node->data);
        node = node->next;
        i++;
    }
    tab[i] = NULL;
    return tab;
}
