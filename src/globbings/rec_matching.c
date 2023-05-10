/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** Build the list of matches for a globbing pattern
*/

#include <stddef.h>
#include <stdlib.h>
#include "globber.h"

static void rec_match_find(char **elems, list_t *res, int depth)
{
    list_t *tmp = NULL;
    node_t *node = NULL;

    node = res->head;
    for (; node; node = node->next) {
        tmp = reslist_from_ppattern(elems, node->data, depth + 1);
        if (!tmp) continue;
        free(node->data);
        node->data = NULL;
        if (tmp->size > 0)
            node->data = str_from_list(tmp);
        list_destroy(tmp, &free_str);
    }
}

list_t *reslist_from_ppattern(char **elems, const char *prefix, int depth)
{
    list_t *res = NULL;

    if (!elems || !elems[depth]) {
        return NULL;
    }
    if (!elems[depth + 1]) {
        res = get_concerned(elems[depth], prefix, &any_concerned);
        add_prefix_to_list(res, prefix);
    } else {
        res = get_concerned(elems[depth], prefix, &dir_concerned);
        add_prefix_to_list(res, prefix);
        rec_match_find(elems, res, depth);
    }
    return res;
}
