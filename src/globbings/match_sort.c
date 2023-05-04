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
#include "mystr.h"
#include "globber.h"

static void sort_step(node_t *i)
{
    char *tmp = NULL;
    node_t *j = NULL;

    for (j = i->next; j; j = j->next) {
        if (strcmp(i->data, j->data) > 0) {
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
    list_t *tmp = NULL;

    if (!matches) {
        return;
    }
    tmp = list_init();
    for (cur = matches->head; cur; cur = cur->next) {
        if (stat(cur->data, &sbuf) == 0 && S_ISDIR(sbuf.st_mode)) {
            tmp->interface->append(
                matches, matches->interface->pop(matches, cur));
        }
    }
}
