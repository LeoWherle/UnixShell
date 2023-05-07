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

ast_t *pre_par_obj(ast_t *node)
{
    ast_t *(*ptr)(ast_t *) = NULL;
    ast_t *new = NULL;

    new = node->left;
    if (new->data == par_close || new->data == par_open) {
        ptr = new->data;
        new = ptr(new);
    }
    free_ast(new->right);
    if (node->right->data == par_open || node->right->data == par_close) {
        ptr = node->right->data;
        new->right = ptr(node->right);
    } else
        new->right = node->right;
    return new;
}

ast_t *par_open(ast_t *node)
{
    ast_t *new = NULL;

    if (node->left->data){
        new = pre_par_obj(node);
    } else {
        if (node->right->data == par_close || node->right->data == par_open)
            new = par_close(node->right);
        else
            new = node->right;
        free_ast(node->left);
    }
    free(node);
    return new;
}

ast_t *par_close(ast_t *node)
{
    ast_t *new = NULL;

    if (node->right->data) {
        if (node->right->data == par_close)
            new = par_close(node->right);
        else
            new = node->right;
        place_node(new, node->left);
    } else {
        new = node->left;
        free(node->right);
    }
    free(node);
    return new;
}
