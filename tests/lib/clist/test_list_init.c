/*
** EPITECH PROJECT, 2023
** graphical [WSL: fedora]
** File description:
** test_list_init
*/

#include <unistd.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "clist.h"

Test(list_init, test_list_init)
{
    list_t *list = NULL;
    list = list_init();

    cr_assert_not_null(list);
    cr_assert_null(list->head);
    cr_assert_null(list->tail);
    cr_assert_eq(list->size, 0);
    cr_assert_not_null(list->interface);
    cr_assert_not_null(list->interface->append);
    cr_assert_not_null(list->interface->insert);
    cr_assert_not_null(list->interface->popf);
    cr_assert_not_null(list->interface->pop);
    cr_assert_not_null(list->interface->append_list);
    cr_assert_not_null(list->interface->insert_list);
    cr_assert_not_null(list->interface->print);
    cr_assert_not_null(list->interface->find);
    cr_assert_not_null(list->interface->destroy);
}

Test(node_init, test_node_init)
{
    node_t *node = NULL;
    node = node_init(NULL);

    cr_assert_not_null(node);
    cr_assert_null(node->data);
    cr_assert_null(node->next);
}

Test(list_init, test_list_one_interface)
{
    list_t *list = NULL;
    list_t *list2 = NULL;

    list = list_init();
    list2 = list_init();
    cr_assert_eq(list->interface, list2->interface);
}

Test(list_init, test_list_insert_empy_list)
{
    list_t *list = NULL;
    list = list_init();

    list->interface->insert(list, "END");
    cr_assert_eq(list->size, 1);
    cr_assert_not_null(list->head);
    cr_assert_not_null(list->tail);
    cr_assert_str_eq(list->head->data, "END");
    cr_assert_str_eq(list->tail->data, "END");
}

Test(list_init, test_list_insert_list)
{
    list_t *list = NULL;
    list = list_init();

    list->interface->insert(list, "END");
    list->interface->insert(list, "MIDDLE");
    list->interface->insert(list, "START");
    cr_assert_eq(list->size, 3);
    cr_assert_not_null(list->head);
    cr_assert_not_null(list->tail);
    cr_assert_str_eq(list->head->data, "START");
    cr_assert_str_eq(list->head->next->data, "MIDDLE");
    cr_assert_str_eq(list->head->next->next->data, "END");
    cr_assert_str_eq(list->tail->data, "END");
}

Test(list_init, test_list_append_empy_list)
{
    list_t *list = NULL;
    list = list_init();

    list->interface->append(list, "START");
    cr_assert_eq(list->size, 1);
    cr_assert_not_null(list->head);
    cr_assert_not_null(list->tail);
    cr_assert_str_eq(list->head->data, "START");
    cr_assert_str_eq(list->tail->data, "START");
}

Test(list_init, test_list_append_list)
{
    list_t *list = NULL;
    list = list_init();

    list->interface->append(list, "START");
    list->interface->append(list, "MIDDLE");
    list->interface->append(list, "END");
    cr_assert_eq(list->size, 3);
    cr_assert_not_null(list->head);
    cr_assert_not_null(list->tail);
    cr_assert_str_eq(list->head->data, "START");
    cr_assert_str_eq(list->head->next->data, "MIDDLE");
    cr_assert_str_eq(list->head->next->next->data, "END");
    cr_assert_str_eq(list->tail->data, "END");
}
