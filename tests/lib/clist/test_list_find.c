/*
** EPITECH PROJECT, 2023
** mypaint [WSL: fedora]
** File description:
** tests_list_find
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <string.h>
#include "clist.h"

Test(list_find, test_list_find_node)
{
    list_t *list = NULL;
    char *str = NULL;

    str = malloc(sizeof(char) * 5);
    strcpy(str, "test");
    list = list_init();
    list->interface->append(list, str);
    cr_assert_eq(list->interface->find(list, str), list->head);
}

Test(list_find, test_list_find_node_not_found)
{
    list_t *list = NULL;
    char *str = NULL;

    str = malloc(sizeof(char) * 5);
    strcpy(str, "test");
    list = list_init();
    list->interface->append(list, str);
    cr_assert_eq(list->interface->find(list, "test2"), NULL);
}
