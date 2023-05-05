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

static void ppattern_step(const char *pattern, int i, int *k, list_t *list)
{
    char *tmp = NULL;

    if (pattern[i] == '/' && (i != 0 && pattern[i - 1] != '\\')) {
        tmp = strndup(pattern + *k, i - *k);
        *k = i + 1;
        if (node_append(list, tmp)) {
            free(tmp);
        }
    }
}

char **parse_pattern(const char *pattern)
{
    list_t *list = NULL;
    char *tmp = NULL;
    int i = 0;
    int k = 0;

    list = list_init();
    while (pattern[i] != '\0') {
        ppattern_step(pattern, i, &k, list);
        i++;
    }
    tmp = strndup(pattern + k, i);
    if (node_append(list, tmp)) {
        free(tmp);
    }
    return list_to_tab(list);
}

void add_prefix_to_str(char **str, const char *prefix)
{
    char *tmp = NULL;

    if (!str || !(*str) || !prefix || prefix[0] == '\0') {
        return;
    }
    tmp = *str;
    *str = malloc(strlen(prefix) + strlen(tmp) + 1);
    ASSERT_MALLOC(*str,);
    strcpy(*str, prefix);
    strcat(*str, "/");
    strcat(*str, tmp);
    free(tmp);
}

int is_valid_pattern(const char *pattern)
{
    int i = 0;

    while (pattern[i]) {
        if (IS_GLOCHAR(pattern[i])) {
            return 1;
        }
        if (pattern[i] == '\\' && pattern[i + 1]) {
            i++;
        }
        i++;
    }
    return 0;
}

void free_str(void *str)
{
    if (str) {
        free(str);
    }
}
