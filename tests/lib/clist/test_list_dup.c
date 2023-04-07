/*
** EPITECH PROJECT, 2023
** 42sh [WSL: fedora]
** File description:
** test_list_dup
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "clist.h"

#define STRING_LIST_H

Test(list_dup, test_list_dup)
{
    list_t *list = NULL;
    list_t *list2 = NULL;

    list = list_init();
    list->interface->append(list, "DATA");
    list->interface->append(list, "DATA2");
    list->interface->append(list, "DATA3");
    list->interface->append(list, "DATA4");
    list2 = list_dup(list, &string_dup);
    cr_assert_eq(list->size, 4);
    cr_assert_not_null(list2);
    cr_assert_eq(list2->size, 4);
    cr_assert_str_eq(list2->head->data, "DATA");
    cr_assert_str_eq(list2->head->next->data, "DATA2");
    cr_assert_str_eq(list2->head->next->next->data, "DATA3");
    cr_assert_str_eq(list2->head->next->next->next->data, "DATA4");
    cr_assert_null(list2->head->next->next->next->next);
}

Test(list_dup, test_list_dup_empty)
{
    list_t *list = NULL;
    list_t *list2 = NULL;

    list = list_init();
    list2 = list_dup(list, &string_dup);
    cr_assert_eq(list->size, 0);
    cr_assert_not_null(list2);
    cr_assert_eq(list2->size, 0);
    cr_assert_null(list2->head);
}

Test(list_dup, test_list_dup_null)
{
    list_t *list2 = NULL;

    list2 = list_dup(NULL, NULL);
    cr_assert_null(list2);
}
