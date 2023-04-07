/*
** EPITECH PROJECT, 2023
** mypaint [WSL: fedora]
** File description:
** chained_list_build
*/

#include <stdlib.h>
#include "clist.h"

/**
 * @brief Build an array of void * from a list
 *
 * @param list the list to build from
 * @return void** an array of void * or NULL if an error occured
 */
void **array_build(list_t *list)
{
    void **array = NULL;
    node_t *node = NULL;
    int i = 0;

    if (list == NULL || list->size == 0)
        return NULL;
    array = malloc(sizeof(void *) * (list->size + 1));
    ASSERT_MALLOC(array, NULL)
    node = list->head;
    while (node != NULL) {
        array[i] = node->data;
        node = node->next;
        i++;
    }
    array[i] = NULL;
    return array;
}

/**
 * @brief Build a list from an array of char *
 *
 * @param array an array of char * must be NULL terminated
 * @return list_t* a pointer to the list or NULL if an error occured
 */
list_t *list_build(char **array)
{
    list_t *list = NULL;
    int i = 0;

    if (array == NULL)
        return NULL;
    list = list_init();
    ASSERT_MALLOC(list, NULL)
    while (array[i] != NULL) {
        node_append(list, (void *)array[i]);
        i++;
    }
    return list;
}
