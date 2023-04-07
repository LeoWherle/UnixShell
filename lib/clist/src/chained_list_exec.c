/*
** EPITECH PROJECT, 2023
** graphical [WSL: fedora]
** File description:
** chained_list_exec
*/

#include <stdlib.h>
#include "clist.h"

/**
 * @brief execute a function on all the data of a list
 *
 * @param list the list to execute on
 * @param exec_data the function to execute
 */
void list_foreach(list_t *list, fun_foreach exec_data)
{
    node_t *node = NULL;

    if (list == NULL || exec_data == NULL)
        return;
    node = list->head;
    while (node != NULL) {
        exec_data(node->data);
        node = node->next;
    }
}

/**
 * @brief execute a function on all the data of a list
 *
 * @param list the list to execute on
 * @param exec_data the function to execute
 * @param arg1 optional arguement for the function
 * @param arg2 second optional arguement for the function
 */
void list_foreach_wargs(list_t *list, fun_foreach_wargs exec_data,
void *arg1, void *arg2)
{
    node_t *node = NULL;

    if (list == NULL || exec_data == NULL)
        return;
    node = list->head;
    while (node != NULL) {
        exec_data(node->data, arg1, arg2);
        node = node->next;
    }
}
