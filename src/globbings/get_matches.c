/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** Build the list of matches for a globbing pattern
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include "globber.h"
#include "clist.h"

list_t *get_contained_matching(const char *pattern, const char *prefix)
{
    DIR *dir = NULL;
    list_t *list = NULL;
    struct dirent *entry;

    dir = opendir(prefix);
    if (dir == NULL) {
        return NULL;
    }
    list = list_init();
    while ((entry = readdir(dir)) != NULL) {
        if (is_match(pattern, entry->d_name)) {
            list->interface->append(list, strdup(entry->d_name));
        }
    }
    closedir(dir);
    return list;
}

list_t *get_dir_contained_matching(const char *pattern, const char *prefix)
{
    DIR *dir = NULL;
    list_t *list = NULL;
    struct dirent *entry;
    struct stat statbuf;

    dir = opendir(prefix);
    list = list_init();
    while ((entry = readdir(dir)) != NULL) {
        stat(entry->d_name, &statbuf);
        if (is_match(pattern, entry->d_name) && S_ISDIR(statbuf.st_mode)) {
            list->interface->append(list, strdup(entry->d_name));
        }
    }
    closedir(dir);
    return list;
}

void rec_match_find(list_t *elems, list_t *res)
{
    list_t *tmp = NULL;
    node_t *node = NULL;

    node = res->head;
    while (node) {
        tmp = reslist_from_ppattern(elems, node->data);
        node->data = str_from_list(tmp);
        node = node->next;
    }
}
