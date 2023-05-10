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

static const escchartype_t ctrl_escapechars[] = {
    {'D', ctrl_left_arrow},
    {'C', ctrl_right_arrow},
    {EOF, NULL},
};

static const escchartype_t shift_escapechars[] = {
    {'C', right_arrow},
    {'D', left_arrow},
    {EOF, NULL},
};

// for some reason, the escape sequence for ctrl+left and ctrl+right is
// 1;5D and 1;5C, and of 1;2D and 1;2C, respectively, when using the
static const escchartypetype_t comb_escapechars[] = {
    {'5', ctrl_escapechars},
    {'2', shift_escapechars},
};

// simplified version of esc_combination_key that only handles ctrl+left and
// ctrl+right
// I keep it here in case somebody needs to understand how esc_combination_key
// works as it is a bit more complicated
UNUSED static int esc_ctrl_key(textfield_t *field, char seq[], head_t *head)
{
    seq[0] = getchar();
    if (seq[0] != '5') {
        return 0;
    }
    seq[0] = getchar();
    for (unsigned int i = 0; comb_escapechars->type != EOF; i++) {
        if (seq[0] == ctrl_escapechars[i].type) {
            return ctrl_escapechars[i].handler(field, seq, head);
        }
    }
    return 0;
}

// handle the combination key (ctrl+left, ctrl+right, shift+left, shift+right)
static int esc_combi_key_handle(textfield_t *field, char seq[], head_t *head,
    escchartype_t const *comb_escapechars)
{
    for (unsigned int i = 0; comb_escapechars->type != EOF; i++) {
        if (seq[0] == comb_escapechars[i].type) {
            return comb_escapechars[i].handler(field, seq, head);
        }
    }
    return 0;
}

// get the combination key and call the handler for the combination
static int esc_combination_key(textfield_t *field, char seq[], head_t *head)
{
    seq[0] = getchar();
    for (unsigned int i = 0; i < TAB_SIZE(comb_escapechars); i++) {
        if (seq[0] == comb_escapechars[i].type) {
            seq[0] = getchar();
            return esc_combi_key_handle(field, seq, head,
                comb_escapechars[i].handler);
        }
    }
    return 0;
}

// esc_combinations could be generalized to handle any combination of keys
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
    if (seq[0] == '1' && seq[1] == ';') {
        return esc_combination_key(field, seq, head);
    }
    return 0;
}
