/*
** EPITECH PROJECT, 2023
** minishell2 [WSL: fedora]
** File description:
** chained_list_dup
*/

#include <stdlib.h>
#include "clist.h"

void *string_dup(void *data)
{
    int len = 0;
    int index = 0;
    char *new_data = NULL;

    ASSERT_MALLOC(data, NULL)
    for (; ((char *)data)[len] != '\0'; len++);
    new_data = malloc(sizeof(char) * (len + 1));
    ASSERT_MALLOC(new_data, NULL)
    for (index = 0; index < len; index++)
        new_data[index] = ((char *)data)[index];
    new_data[index] = '\0';
    return (void *)new_data;
}

/**
 * @brief duplicate a list
 *
 * @param list the list to duplicate
 * @param dup_data function to duplicate the data
 * @return list_t* the new list
 */
list_t *list_dup(list_t *list, any_t (*dup_data)(any_t data))
{
    list_t *new_list = NULL;
    node_t *node = NULL;
    any_t data = NULL;

    if (list == NULL || dup_data == NULL)
        return NULL;
    new_list = list_init();
    ASSERT_MALLOC(new_list, NULL)
    node = list->head;
    while (node != NULL) {
        data = dup_data(node->data);
        ASSERT_MALLOC(data, NULL)
        node_append(new_list, node->data);
        node = node->next;
    }
    return new_list;
}
