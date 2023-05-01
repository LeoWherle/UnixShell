/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** check node
*/

#include <stdbool.h>
#include "ast.h"

bool check_nb_par(ast_t *node)
{
    if (node->data == par_open) {
        if (node->right->data != par_close) {
            WRITE_MUCH_OPEN;
            return false;
        }
    }
    if (node->right->data == par_close && node->data != par_open) {
        WRITE_MUCH_CLOSE;
        return false;
    }
    return true;
}

bool check_ambiguous_redir(ast_t *node)
{
    if (node->data == use_pipe) {
        if (node->right->data == use_din || node->right->data == use_in ||
            node->left->data == use_dout || node->left->data == use_out) {
            WRITE_AMB_R;
            return false;
        }
    }
    return true;
}

bool check_null(ast_t *node)
{
    if (node->left->data == NULL || node->right->data == NULL) {
        if (node->data == par_open || node->data == par_close) {
            return true;
        }
        if (node->data == use_din || node->data == use_dout ||
            node->data == use_in || node->data == use_out) {
            WRITE_NULL_R;
            return false;
        }
        WRITE_NULL_S;
        return false;
    }
    return true;
}

bool check_tree(ast_t *node, int i)
{
    if (i == 0 && node->data == par_close) {
        WRITE_MUCH_CLOSE;
        return false;
    }
    if (node->type == COMMAND)
        return true;
    if (!check_nb_par(node))
        return false;
    if (!check_ambiguous_redir(node))
        return false;
    if (!check_null(node))
        return false;
    if (!check_tree(node->right, i + 1))
        return false;
    return check_tree(node->left, i + 1);
}
