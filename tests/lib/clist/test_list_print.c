/*
** EPITECH PROJECT, 2023
** mypaint [WSL: fedora]
** File description:
** test_list_print
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <string.h>
#include <unistd.h>
#include "clist.h"

void print_string(void *data)
{
    char *str = (char *)data;

    write(1, str, strlen(str));
}

void redirect_all_stdout(void) {
    cr_redirect_stdout();
}

TestSuite(list_print, .init = redirect_all_stdout);

Test(list_print, test_list_print_no_delim)
{
    list_t *list = NULL;
    char *str = NULL;

    str = malloc(sizeof(char) * 5);
    strcpy(str, "test");
    str[4] = '\0';
    list = list_init();
    list->interface->append(list, str);

    list_print(list, &print_string, NULL);
    fflush(stdout);
    cr_assert_stdout_eq_str("test");
}

Test(list_print, test_list_print_delim_one)
{
    list_t *list = NULL;
    char *str = NULL;

    str = malloc(sizeof(char) * 5);
    strcpy(str, "test");
    str[4] = '\0';
    list = list_init();
    list->interface->append(list, str);

    list_print(list, &print_string, "\n");
    fflush(stdout);
    cr_assert_stdout_eq_str("test");
}

Test(list_print, test_list_print_delim_two)
{
    list_t *list = NULL;
    char *str = NULL;

    str = malloc(sizeof(char) * 5);
    strcpy(str, "test");
    str[4] = '\0';
    list = list_init();
    list->interface->append(list, str);
    list->interface->append(list, str);

    list_print(list, &print_string, "\n");
    fflush(stdout);
    cr_assert_stdout_eq_str("test\ntest");
}
