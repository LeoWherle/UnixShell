/*
** EPITECH PROJECT, 2023
** Personal_Clib [WSL: fedora]
** File description:
** chained_list_print
*/

#include <stdlib.h>
#include <unistd.h>
#include "clist.h"

static void my_putstr(const char *str)
{
    int i = 0;

    for (; str[i] != '\0'; i++);
    write(1, str, i);
}

/**
 * @brief Print the list
 *
 * @param list the list
 * @param print_data function to print the data
 * @param separator the separator between each data
 */
void list_print(list_t *list, void (*print_data)(void *), const char *separator)
{
    node_t *node = NULL;

    node = list->head;
    while (node != NULL) {
        print_data(node->data);
        if (node->next != NULL)
            my_putstr(separator);
        node = node->next;
    }
}
