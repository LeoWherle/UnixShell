/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** par
*/

#include <stdlib.h>
#include "ast.h"
#include "errorhandling.h"
#include "mysh.h"

int par_open(ast_t *node, int to_read, int to_write, head_t *head)
{
    if (node->left->type == SEP) {
        free_matrix(node->left->right->data);
        free(node->left->right);
        node->left->right = node->right;
        node->right = NULL;
        return execute(node->left, to_read, to_write, head);
    }
    return execute(node->right, to_read, to_write, head);
}

int par_close(ast_t *node, int to_read, int to_write, head_t *head)
{
    if (node->right->type == SEP) {
        free_matrix(node->right->left->data);
        free(node->right->left);
        node->right->left = node->left;
        node->left = NULL;
        return execute(node->right, to_read, to_write, head);
    }
    return execute(node->left, to_read, to_write, head);
}
