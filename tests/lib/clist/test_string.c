/*
** EPITECH PROJECT, 2023
** 42sh [WSL: fedora]
** File description:
** test_string
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#define STRING_LIST_H
#include "clist.h"


Test(string, test_string)
{
    char *str = NULL;

    str = string_dup("test");
    cr_assert_str_eq(str, "test");
    string_free(str);
}

Test(string, test_string_null)
{
    char *str = NULL;

    string_free(str);
    cr_assert_null(str);
}
