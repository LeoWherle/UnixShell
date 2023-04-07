/*
** EPITECH PROJECT, 2023
** mypaint [WSL: fedora]
** File description:
** test_list_destroy
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <string.h>
#include "clist.h"

void free_string3(any_t data)
{
    free(data);
}

Test(list_destroy, test_list_destroy_node)
{
    list_t *list = NULL;
    char *str = NULL;

    str = malloc(sizeof(char) * 5);
    strcpy(str, "test");
    list = list_init();
    list->interface->append(list, str);
    node_destroy(list, &free_string3);
    cr_assert_eq(list->head, NULL);
    cr_assert_eq(list->tail, NULL);
    cr_assert_eq(list->size, 0);
}

Test(list_destroy, test_list_delete_node)
{
    list_t *list = NULL;
    char *str = NULL;

    str = malloc(sizeof(char) * 5);
    strcpy(str, "test");
    list = list_init();
    list->interface->append(list, str);
    cr_expect_eq(list->head->data, str);
    cr_expect_eq(list->tail->data, str);
    node_delete(list, str, &free_string3);
    cr_assert_eq(list->size, 0);
    cr_assert_eq(list->head, NULL);
    cr_assert_eq(list->tail, NULL);
}

Test(list_destroy, test_list_delete_node_muliple)
{
    list_t *list = NULL;
    char *str1 = NULL;
    char *str2 = NULL;
    char *str3 = NULL;

    str1 = malloc(sizeof(char) * 6);
    strcpy(str1, "test1");
    str2 = malloc(sizeof(char) * 6);
    strcpy(str2, "test2");
    str3 = malloc(sizeof(char) * 6);
    strcpy(str3, "test3");
    list = list_init();
    list->interface->append(list, str1);
    list->interface->append(list, str2);
    list->interface->append(list, str3);
    node_delete(list, str3, &free_string3);
    cr_assert_eq(list->head->data, str1);
    cr_assert_eq(list->tail->data, str2);
    cr_assert_eq(list->size, 2);
}

Test(list_destroy, test_list_delete_node_muliple2)
{
    list_t *list = NULL;
    char *str = NULL;
    char *str2 = NULL;

    str = malloc(sizeof(char) * 5);
    strcpy(str, "test");
    str2 = malloc(sizeof(char) * 6);
    strcpy(str2, "test2");
    list = list_init();
    list->interface->append(list, str);
    list->interface->append(list, str2);
    node_delete(list, str, &free_string3);
    cr_assert_eq(list->head->data, str2);
    cr_assert_eq(list->tail->data, str2);
    cr_assert_eq(list->size, 1);
}

// Can't test this function assert_free missing
Test(list_destroy, test_list_destroy_list)
{
    list_t *list = NULL;
    char *str = NULL;
    char *str2 = NULL;

    str = malloc(sizeof(char) * 5);
    strcpy(str, "test");
    str2 = malloc(sizeof(char) * 6);
    strcpy(str2, "test2");
    list = list_init();
    list->interface->append(list, str);
    list->interface->append(list, str2);
    list_destroy(list, &free_string3);
}
