/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** head
*/

#include <stdlib.h>
#include "clist.h"
#include "mysh.h"
#include "rcfile.h"
#include "history.h"

bool create_head(head_t *head, char * const *e)
{
    create_rc_file(head);
    if (!head->alias)
        return false;
    make_env(e, head);
    if (!head->first)
        return false;
    head->path = find_path(head->first);
    head->history = list_init();
    if (!head->history)
        return false;
    return true;
}

void free_head(head_t *head)
{
    free_env(head->first);
    free(head->home);
    free(head->old);
    if (head->path)
        free_matrix(head->path);
    list_destroy(head->history, histroy_destroy);
}
