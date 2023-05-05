/*
** EPITECH PROJECT, 2023
** 42sh [WSL: fedora]
** File description:
** ansi_handle
*/

#include <stdio.h>
#include <string.h>
#include "prompt.h"
#include "mystr.h"
#include "errorh.h"

// ANSI escape sequences
static const escchartype_t escapechars[] = {
    {'A', up_arrow},
    {'B', down_arrow},
    {'C', right_arrow},
    {'D', left_arrow},
    {'3', delete_key},
};

int esc_key(textfield_t *field, head_t *head)
{
    char seq[3];

    if (getchar() == '[') {
        seq[0] = getchar();
        if (seq[0] >= '0' && seq[0] <= '9') {
            seq[1] = getchar();
        }
    }
    for (unsigned int i = 0; i < TAB_SIZE(escapechars); i++) {
        if (seq[0] == escapechars[i].type) {
            return escapechars[i].handler(field, seq, head);
        }
    }
    return 0;
}
