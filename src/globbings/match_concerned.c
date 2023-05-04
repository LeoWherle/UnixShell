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
#include "errorh.h"

void any_concerned(list_t *list, const char *pattern,
    UNUSED const char *prefix, const char *entryn)
{
    if (is_match(pattern, entryn)) {
        list->interface->append(list, strdup(entryn));
    }
}

void dir_concerned(
    list_t *list, const char *pattern, const char *prefix, const char *entryn)
{
    struct stat statbuf;
    char *tmp = strdup(entryn);

    tmp = strdup(entryn);
    add_prefix_to_str(&tmp, prefix);
    stat(tmp, &statbuf);
    if (is_match(pattern, entryn) && S_ISDIR(statbuf.st_mode)) {
        list->interface->append(list, strdup(entryn));
    }
}

list_t *get_concerned(const char *pattern, const char *prefix,
    void (*assert)(list_t *, const char *, const char *, const char *))
{
    DIR *dir = NULL;
    list_t *list = NULL;
    struct dirent *entry;

    if (prefix[0] == '\0') {
        dir = opendir(".");
    } else {
        dir = opendir(prefix);
    }
    list = list_init();
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.' && pattern[0] != '.') {
            continue;
        }
        assert(list, pattern, prefix, entry->d_name);
    }
    closedir(dir);
    return list;
}
