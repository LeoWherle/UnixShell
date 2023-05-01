/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** ast
*/

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ast.h"
#include "errorh.h"
#include "mysh.h"

static const sep_t sep[NB_SEP] = {
    {"(", par_open},
    {")", par_close},
    {";", use_semi_colon},
    {"||", use_or},
    {"&&", use_and},
    {"|", use_pipe},
    {"<<", use_din},
    {"<", use_in},
    {">>", use_dout},
    {">", use_out},
};

static ast_t *create_node(void *data, enum type type)
{
    ast_t *new = NULL;

    ASSERT_MALLOC(data, NULL);
    new = malloc(sizeof(ast_t));
    ASSERT_MALLOC(new, NULL);
    new->type = type;
    if (type == COMMAND) {
        new->data = my_str_to_word_array(data, ' ');
        free(data);
    } else {
        new->data = data;
    }
    new->left = NULL;
    new->right = NULL;
    return new;
}

void free_ast(ast_t *ast)
{
    if (!ast)
        return;
    if (ast->left)
        free_ast(ast->left);
    if (ast->right)
        free_ast(ast->right);
    if (ast->type == COMMAND)
        free_matrix(ast->data);
    free(ast);
}

static ast_t *divide_text(char *text, int i, int size, int len)
{
    ast_t *new = NULL;

    new = create_node(sep[i].ptr, SEP);
    ASSERT_MALLOC(new, NULL);
    new->left = build_ast(strndup(text, size), i);
    ASSERT_MALLOC(new->left, NULL);
    new->right = build_ast(strdup(&text[size + len]), i);
    ASSERT_MALLOC(new->right, NULL);
    free(text);
    return new;
}

ast_t *build_ast(char *text, int i)
{
    size_t size = 0;
    size_t len = 0;

    if (!text)
        return NULL;
    if (i == NB_SEP)
        return create_node(text, COMMAND);
    len = strlen(sep[i].sep);
    while (text[size] != '\0' && strncmp(&text[size], sep[i].sep, len) != 0)
        size++;
    if (text[size] == '\0')
        return build_ast(text, i + 1);
    return divide_text(text, i, size, len);
}
