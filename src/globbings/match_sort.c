/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** Build the list of matches for a globbing pattern
*/

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include "mystr.h"
#include "globber.h"

static int should_switch(char *str1, char *str2)
{
    int i = 0;

    if (!str1 || !str2) return 0;
    str1 = strdup(str1);
    ASSERT_PTR(str1, 0);
    str2 = strdup(str2);
    if (!str2) {
        free(str1);
        return 0;
    }
    for (; str1[i]; i++)
        str1[i] = tolower(str1[i]);
    for (i = 0; str2[i]; i++)
        str2[i] = tolower(str2[i]);
    i = strcmp(str1, str2);
    free(str1);
    free(str2);
    return i > 0;
}

static void sort_step(node_t *i)
{
    char *tmp = NULL;
    node_t *j = NULL;

    for (j = i->next; j; j = j->next) {
        if (should_switch(i->data, j->data)) {
            tmp = i->data;
            i->data = j->data;
            j->data = tmp;
        }
    }
}

void sort_matches(node_t *head)
{
    node_t *i = NULL;

    if (!head) {
        return;
    }
    for (i = head; i->next; i = i->next) {
        sort_step(i);
    }
}

void move_dirs_to_end(list_t *matches)
{
    struct stat sbuf;
    node_t *cur = NULL;

    if (!matches) {
        return;
    }
    for (cur = matches->head; cur; cur = cur->next) {
        if (stat(cur->data, &sbuf) != 0 || !S_ISDIR(sbuf.st_mode)) {
            continue;
        }
        if (node_append(matches, node_pop(matches, cur))) {
            return;
        }
    }
}
