/*
** EPITECH PROJECT, 2023
** graphical [WSL: fedora]
** File description:
** chained_list_destructor
*/

#include <stdlib.h>
#include "clist.h"

/**
 * @brief free a data only
 *
 * @param data the data to free
 */
void string_free(void *data)
{
    if (data == NULL)
        return;
    free(data);
}
