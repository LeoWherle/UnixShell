/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** Build the list of matches for a globbing pattern
*/

#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "globber.h"

static void free_str(void *data)
{
    if (data)
        free(data);
}

list_t *reslist_from_ppattern(list_t *elems, const char *prefix)
{
    list_t *res = NULL;
    char *pattern = NULL;

    if (!elems || elems->size == 0) {
        return NULL;
    }
    pattern = elems->interface->popf(elems);
    if (elems->size == 0) {
        res = get_contained_matching(pattern, prefix);
        elems->interface->destroy(elems, &free_str);
    } else {
        res = get_dir_contained_matching(pattern, prefix);
        rec_match_find(elems, res);
    }
    free(pattern);
    add_prefix_to_list(res, prefix);
    return res;
}

char *get_all_matches(const char *pattern)
{
    list_t *pparsed = NULL;
    char *prefix = NULL;

    if (pattern[0] == '/') {
        prefix = strdup("/");
    } else {
        prefix = strdup("./");
    }
    pparsed = parse_pattern(pattern);
    return str_from_list(reslist_from_ppattern(pparsed, prefix));
}
