/*
** EPITECH PROJECT, 2023
** 42sh [WSL: fedora]
** File description:
** main
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "clist.h"

void print_string(any_t data, void *arg, void *arg2)
{
    write(1, data, strlen(data));
}

void destroy_stack(any_t data)
{
    return;
}

int main(void)
{
    list_t *list = list_init();
    list->interface->append(list, "Hello");
    list->interface->append(list, "World");
    list->interface->append(list, "!");
    list->interface->print(list, &print_string, " ");
    write(1, "\n", 1);
    list->interface->destroy(list, &destroy_stack);
    return 0;
}
