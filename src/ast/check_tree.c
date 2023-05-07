/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** check node
*/

#include <stdbool.h>
#include "ast.h"

static bool check_close(ast_t *node, int *open, int *close)
{
    *close += 1;
    if (*close > *open) {
        WRITE_MUCH_CLOSE;
        return false;
    }
    if (node->right->type == COMMAND && node->right->data) {
        WRITE_BAD_PLACE;
        return false;
    }
    if (!node->left->data) {
        WRITE_NULL_S;
        return false;
    }
    return true;
}

bool check_par(ast_t *node, int *open, int *close)
{
    if (node->type == COMMAND ||
        (node->data != par_open && node->data != par_close))
        return true;
    if (node->data == par_open) {
        *open += 1;
        if (node->left->type == COMMAND && node->left->data) {
            WRITE_BAD_PLACE;
            return false;
        }
        if (node->right->data != par_open && node->right->data != par_close) {
            WRITE_MUCH_OPEN;
            return false;
        }
    } else if (!check_close(node, open, close))
        return false;
    if (!check_par(node->left, open, close))
        return false;
    return check_par(node->right, open, close);
}

static bool check_ambiguous_redir(ast_t *node)
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

static bool check_null(ast_t *node)
{
    if (node->right->data == NULL) {
        if (node->data == use_din || node->data == use_dout ||
            node->data == use_in || node->data == use_out) {
            WRITE_NULL_R;
            return false;
        }
    }
    if (node->left->data == NULL || node->right->data == NULL) {
        if (node->data == par_open || node->data == par_close) {
            return true;
        }
        if (node->data == use_or ||
            node->data == use_and || node->data == use_pipe) {
            WRITE_NULL_S;
            return false;
        }
    }
    return true;
}

bool check_tree(ast_t *node, int i)
{
    if (node->type == COMMAND)
        return true;
    if (!check_ambiguous_redir(node))
        return false;
    if (!check_null(node))
        return false;
    if (!check_tree(node->right, i + 1))
        return false;
    return check_tree(node->left, i + 1);
}
