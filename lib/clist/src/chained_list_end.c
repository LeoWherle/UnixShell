/*
** EPITECH PROJECT, 2023
** 42sh [WSL: fedora]
** File description:
** chained_list_end
*/

#include "clist.h"
#include <stdlib.h>

void list_end(void)
{
    list_t *list = NULL;

    list = list_init();
    if (list == NULL)
        return;
    free(list->interface);
    free(list);
}
