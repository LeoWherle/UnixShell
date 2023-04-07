/*
** EPITECH PROJECT, 2023
** graphical [WSL: fedora]
** File description:
** chained_list_concat
*/

#include <stdlib.h>
#include "clist.h"

/**
 * @brief add list_src to the end of list_dest
 *
 * @param list_dest the list to add to
 * @param list_src the list to add becomes empty (should be freed, or reused)
 */
void list_append(list_t *list_dest, list_t *list_src)
{
    ASSERT_MALLOC(list_dest,)
    ASSERT_MALLOC(list_src,)
    ASSERT_MALLOC(list_src->head,)
    if (list_dest->head == NULL) {
        list_dest->head = list_src->head;
    } else {
        list_dest->tail->next = list_src->head;
        list_src->head->prev = list_dest->tail;
    }
    list_dest->tail = list_src->tail;
    list_src->head = NULL;
    list_src->tail = NULL;
    list_dest->size += list_src->size;
    list_src->size = 0;
}

/**
 * @brief add list_src to the start of list_dest
 *
 * @param list_dest the list to add to
 * @param list_src the list to add becomes empty (should be freed, or reused)
 */
void list_insert(list_t *list_dest, list_t *list_src)
{
    ASSERT_MALLOC(list_dest,)
    ASSERT_MALLOC(list_src,)
    ASSERT_MALLOC(list_src->head,)
    if (list_dest->head == NULL) {
        list_dest->tail = list_src->tail;
    } else {
        list_src->tail->next = list_dest->head;
        list_dest->head->prev = list_src->tail;
    }
    list_dest->head = list_src->head;
    list_src->head = NULL;
    list_src->tail = NULL;
    list_dest->size += list_src->size;
    list_src->size = 0;
}
