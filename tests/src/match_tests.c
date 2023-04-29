/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** Test if a string match a globbing pattern
*/

#include <criterion/criterion.h>
#include "globber.h"

Test(is_match_tests, simple_test)
{
    cr_assert_eq(is_match("test", "test"), 1);
    cr_assert_eq(is_match("test", "toto"), 0);
    cr_assert_eq(is_match("", ""), 1);
}

Test(is_match_tests, asterisk_test)
{
    cr_assert_eq(is_match("t*", "test"), 1);
    cr_assert_eq(is_match("t*", "t"), 0);
    cr_assert_eq(is_match("*t", "test"), 1);
    cr_assert_eq(is_match("*", "test"), 1);
    cr_assert_eq(is_match("*es*", "test"), 1);
    cr_assert_eq(is_match("*es*", "woweswow"), 1);
}

Test(is_match_tests, qmark_test)
{
    cr_assert_eq(is_match("t?st", "test"), 1);
    cr_assert_eq(is_match("t??t", "tttt"), 1);
    cr_assert_eq(is_match("t?st", "t"), 0);
}

Test(is_match_tests, inhibitor_test)
{
    cr_assert_eq(is_match("\\?", "?"), 1);
    cr_assert_eq(is_match("\\\\", "\\"), 1);
}

Test(is_match_tests, complex_test)
{
    cr_assert_eq(is_match("??w\\?", "Wow?"), 1);
    cr_assert_eq(is_match("*wow?wow\\?", "TracteurwowAwow?"), 1);
    cr_assert_eq(is_match("Oui*Non???\\?", "OuiPinaNonOuiNonColadaNonOui?"), 1);
    cr_assert_eq(is_match("Oui*Non???\\?", "OuiOuiOuiPinaColadaNonOui?"), 1);
    cr_assert_eq(is_match("Oui*Non???\\?", "OuiOuiOuiPinaColadaNon?"), 0);
}

Test(is_match_tests, break_test)
{
    cr_assert_eq(is_match("?????????", ""), 0);
    cr_assert_eq(is_match("?????????", "test"), 0);
    cr_assert_eq(is_match("????????", "testtest"), 1);
    cr_assert_eq(is_match("********", "testtest"), 1);
    cr_assert_eq(is_match("*********", "testtest"), 0);
    cr_assert_eq(is_match("*********", ""), 0);
    cr_assert_eq(is_match("", "test"), 0);
    cr_assert_eq(is_match("test", ""), 0);
    cr_assert_eq(is_match("", NULL), 0);
    cr_assert_eq(is_match(NULL, ""), 0);
    cr_assert_eq(is_match(NULL, NULL), 0);
}

Test(is_match_tests, to_clarify_test)
{
    cr_assert_eq(is_match("**?**\\?*?**", "abcde?fghi"), 1);
    cr_assert_eq(is_match("*?*?*?", "tes"), 0);
    cr_assert_eq(is_match("*?*?*?", "test!?"), 1);
}
