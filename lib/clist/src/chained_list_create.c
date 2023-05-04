/*
** EPITECH PROJECT, 2023
** Personal_Clib [WSL: fedora]
** File description:
** chained_list_create
*/

#include <stdlib.h>
#include "clist.h"

static list_interface_t *init_interface(void)
{
    list_interface_t *interface = NULL;

    interface = malloc(sizeof(list_interface_t));
    ASSERT_MALLOC(interface, NULL)
    interface->append = node_append;
    interface->insert = node_insert;
    interface->popf = node_popf;
    interface->pop = node_pop;
    interface->append_list = list_append;
    interface->insert_list = list_insert;
    interface->print = list_print;
    interface->find = node_find;
    interface->destroy = list_destroy;
    return interface;
}

/**
 * @brief Create a list
 *
 * @return list_t* return a pointer to the list
 */
list_t *list_init(void)
{
    static list_interface_t *interface = NULL;
    list_t *list = NULL;

    list = malloc(sizeof(list_t));
    ASSERT_MALLOC(list, NULL)
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    if (interface == NULL) {
        list->interface = init_interface();
        ASSERT_MALLOC(list->interface, NULL)
        interface = list->interface;
    } else {
        list->interface = interface;
    }
    return (list);
}

node_t *node_init(any_t data)
{
    node_t *node = NULL;

    node = malloc(sizeof(node_t));
    ASSERT_MALLOC(node, NULL)
    node->data = data;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

/**
 * @brief Add a node at the end of the list
 *
 * @param list the list
 * @param data a void * to the data
 * @return int return 0 if success, 1 if error
 */
int node_append(list_t *list, any_t data)
{
    node_t *node = NULL;

    node = node_init(data);
    ASSERT_MALLOC(node, 1)
    if (!list->head) {
        list->head = node;
    } else {
        list->tail->next = node;
        node->prev = list->tail;
    }
    list->tail = node;
    list->size++;
    return 0;
}

/**
 * @brief Add a node at the beginning of the list
 *
 * @param list the list
 * @param data a void * to the data
 * @return int return 0 if success, 1 if error
 */
int node_insert(list_t *list, any_t data)
{
    node_t *node = NULL;

    node = node_init(data);
    ASSERT_MALLOC(node, 1)
    if (!list->head) {
        list->tail = node;
    } else {
        node->next = list->head;
        list->head->prev = node;
    }
    list->head = node;
    list->size++;
    return 0;
}
