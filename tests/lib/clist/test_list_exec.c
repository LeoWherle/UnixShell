/*
** EPITECH PROJECT, 2023
** mypaint [WSL: fedora]
** File description:
** test_list_exec
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "clist.h"

void ceasar_cipher(void *data)
{
    char *str = (char *)data;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] = (str[i] - 'a' + 3) % 26 + 'a';
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] = (str[i] - 'A' + 3) % 26 + 'A';
    }
}

Test(list_foreach, test_list_exec)
{
    list_t *list = NULL;
    char *str = NULL;

    str = malloc(sizeof(char) * 5);
    strcpy(str, "test");
    list = list_init();
    list->interface->append(list, str);
    list_foreach(list, ceasar_cipher);
    cr_assert_str_eq(list->head->data, "whvw");
}

Test(list_foreach, test_list_exec_multiple)
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
    list_foreach(list, ceasar_cipher);
    cr_assert_str_eq(list->head->data, "whvw1");
    cr_assert_str_eq(list->head->next->data, "whvw2");
    cr_assert_str_eq(list->head->next->next->data, "whvw3");
}

Test(list_foreach, test_list_exec_empty)
{
    list_t *list = NULL;

    list_foreach(list, ceasar_cipher);
    cr_assert_eq(list, NULL);
}

void ceasar_cipher2(void *data, void *args, UNUSED void *args2)
{
    char *str = (char *)data;
    int *key = (int *)args;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] = (str[i] - 'a' + *key) % 26 + 'a';
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] = (str[i] - 'A' + *key) % 26 + 'A';
    }
}

Test(list_foreach_wargs, null)
{
    list_t *list = NULL;
    char *str = NULL;
    int key = 3;

    str = malloc(sizeof(char) * 5);
    strcpy(str, "test");
    list = list_init();
    list->interface->append(list, str);
    list_foreach_wargs(list, ceasar_cipher2, &key, NULL);
    cr_assert_str_eq(list->head->data, "whvw");
}

Test(list_foreach_wargs, test_list_foreach_wargs)
{
    list_t *list = NULL;
    char *str1 = NULL;
    char *str2 = NULL;
    char *str3 = NULL;
    int key = 3;

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
    list_foreach_wargs(list, ceasar_cipher2, &key, NULL);
    cr_assert_str_eq(list->head->data, "whvw1");
    cr_assert_str_eq(list->head->next->data, "whvw2");
    cr_assert_str_eq(list->head->next->next->data, "whvw3");
}

Test(list_foreach_wargs, test_null)
{
    list_t *list = NULL;

    list_foreach_wargs(list, ceasar_cipher2, NULL, NULL);
    cr_assert_eq(list, NULL);
}