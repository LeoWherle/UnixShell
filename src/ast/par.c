/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** par
*/

#include <stdlib.h>
#include <stdbool.h>
#include "ast.h"
#include "errorh.h"
#include "mysh.h"

bool place_node(ast_t *dest, ast_t *packet)
{
    if (dest->type == COMMAND)
        return false;
    if (!dest->left->data) {
        free_ast(dest->left);
        dest->left = packet;
        return true;
    }
    if (!dest->right->data) {
        free_ast(dest->right);
        dest->right = packet;
        return true;
    }
    if (place_node(dest->left, packet))
        return true;
    return place_node(dest->right, packet);
}

ast_t *priority(ast_t *left, ast_t *right, bool *post)
{
    if (*post && right->order < left->order) {
        left->right = right->left;
        right->left = left;
        return right;
    }
    left->right = right;
    return left;
}

ast_t *pre_par_obj(ast_t *node, bool *post)
{
    ast_t *(*ptr)(ast_t *, bool *) = NULL;
    ast_t *left = NULL;
    ast_t *right = NULL;
    left = node->left;
    if (left->data == par_close || left->data == par_open) {
        ptr = left->data;
        left = ptr(left, post);
    }
    free_ast(left->right);
    if (node->right->data == par_open || node->right->data == par_close) {
        ptr = node->right->data;
        right = ptr(node->right, post);
    } else
        right = node->right;
    return priority(left, right, post);
}

ast_t *par_open(ast_t *node, bool *post)
{
    ast_t *new = NULL;

    if (node->left->data){
        new = pre_par_obj(node, post);
    } else {
        if (node->right->data == par_close || node->right->data == par_open)
            new = par_close(node->right, post);
        else
            new = node->right;
        free_ast(node->left);
    }
    free(node);
    return new;
}

ast_t *par_close(ast_t *node, bool *post)
{
    ast_t *new = NULL;

    if (node->right->data) {
        if (node->right->data == par_close)
            new = par_close(node->right, post);
        else
            new = node->right;
        place_node(new, node->left);
        *post = true;
    } else {
        new = node->left;
        free(node->right);
        *post = false;
    }
    free(node);
    return new;
}
