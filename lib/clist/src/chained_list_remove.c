/*
** EPITECH PROJECT, 2023
** graphical [WSL: fedora]
** File description:
** chained__list_remove
*/

#include <stdlib.h>
#include "clist.h"

/**
 * @brief removes the first node from the list and returns the data
 * destroys the node
 *
 * @param list the list to remove from
 * @return void* the data from the node
 */
void *node_popf(list_t *list)
{
    node_t *node = NULL;

    ASSERT_MALLOC(list->head, NULL)
    node = list->head;
    list->head = node->next;
    if (list->head != NULL)
        list->head->prev = NULL;
    else
        list->tail = NULL;
    list->size--;
    return node->data;
}

/**
 * @brief removes the last node from the list and returns the data
 * destroys the node
 *
 * @param list the list to remove from
 * @return void* the data from the node
 */
static void *pop_node_data(list_t *list, any_t data)
{
    node_t *node = NULL;

    node = node_find(list, data);
    ASSERT_MALLOC(node, NULL)
    if (node == list->head) {
        data = node_popf(list);
    } else {
        node->prev->next = node->next;
        if (node->next != NULL)
            node->next->prev = node->prev;
        data = node->data;
        list->size--;
        if (node == list->tail)
            list->tail = node->prev;
        free(node);
    }
    return data;
}

static void *pop_last_node(list_t *list)
{
    node_t *node = NULL;
    node_t *temp = NULL;
    any_t data = NULL;

    ASSERT_MALLOC(list->head, NULL)
    temp = list->head;
    node = list->tail;
    while (temp->next != node) {
        temp = temp->next;
    }
    temp->next = NULL;
    data = node->data;
    list->tail = temp;
    list->size--;
    free(node);
    return data;
}

/**
 * @brief removes the last node from the list and returns the data
 * destroys the node if data is NULL else removes the node containing the data
 *
 * @param list the list to remove from
 * @param data if not NULL, the data to remove
 * @return void* the data from the popped node NULL if not found or
 * if list is empty
 */
void *node_pop(list_t *list, any_t data)
{
    ASSERT_MALLOC(list->head, NULL)
    if (data == NULL) {
        if (list->size == 1)
            data = node_popf(list);
        else
            data = pop_last_node(list);
    } else {
        data = pop_node_data(list, data);
    }
    return data;
}
