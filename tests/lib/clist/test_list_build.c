/*
** EPITECH PROJECT, 2023
** mypaint [WSL: fedora]
** File description:
** test_array_build
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "clist.h"

Test(array_build, test_array_build)
{
    list_t *list = NULL;
    char **array = NULL;

    list = list_init();
    list->interface->append(list, "DATA");
    list->interface->append(list, "DATA2");
    list->interface->append(list, "DATA3");
    list->interface->append(list, "DATA4");
    array = (char **)array_build(list);
    cr_assert_eq(list->size, 4);
    cr_assert_not_null(array);
    cr_assert_str_eq(array[0], "DATA");
    cr_assert_str_eq(array[1], "DATA2");
    cr_assert_str_eq(array[2], "DATA3");
    cr_assert_str_eq(array[3], "DATA4");
    cr_assert_null(array[4]);
}

Test(array_build, test_array_build_empty)
{
    list_t *list = NULL;
    char **array = NULL;

    list = list_init();
    array = (char **)array_build(list);
    cr_assert_eq(list->size, 0);
    cr_assert_null(array);
}

Test(array_build, test_array_build_null)
{
    char **array = NULL;

    array = (char **)array_build(NULL);
    cr_assert_null(array);
}



Test(list_build, test_list_build)
{
    list_t *list = NULL;
    char **array = NULL;

    array = malloc(sizeof(char *) * 5);
    array[0] = "DATA";
    array[1] = "DATA2";
    array[2] = "DATA3";
    array[3] = "DATA4";
    array[4] = NULL;
    list = list_build(array);
    cr_assert_eq(list->size, 4);
    cr_assert_not_null(list);
    cr_assert_str_eq(list->head->data, "DATA");
    cr_assert_str_eq(list->head->next->data, "DATA2");
    cr_assert_str_eq(list->head->next->next->data, "DATA3");
    cr_assert_str_eq(list->head->next->next->next->data, "DATA4");
    cr_assert_null(list->head->next->next->next->next);
}

Test(list_build, test_list_build_empty)
{
    list_t *list = NULL;
    char **array = NULL;

    array = malloc(sizeof(char *) * 1);
    array[0] = NULL;
    list = list_build(array);
    cr_assert_eq(list->size, 0);
    cr_assert_not_null(list);
    cr_assert_null(list->head);
}

Test(list_build, test_list_build_null)
{
    list_t *list = NULL;

    list = list_build(NULL);
    cr_assert_null(list);
}
