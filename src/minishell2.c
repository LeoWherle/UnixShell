/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** minishell2
*/

#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include "mysh.h"
#include "ast.h"
#include "history.h"

void create_rc_file(head_t *head)
{
    int fd = open(".42rc", O_CREAT | O_RDWR, 0664);

    if (fd == -1)
        return;
    head->alias = get_alias_list();
    close(fd);
}

bool only_st(char *line)
{
    int i = 0;

    while ((line[i] == ' ' || line[i] == '\t') && line[i] != '\0')
        i++;
    if (line[i] == '\0') {
        return true;
    }
    return false;
}

char *pre_parsing(char *command_line, head_t *head)
{
    command_line = pick_history(command_line, head);
    if (!command_line)
        return NULL;
    command_line = change_command(command_line, head);
    if (!command_line) {
        head->lr = 84;
        return NULL;
    }
    return command_line;
}

ast_t *post_parsing(ast_t *command_tree, head_t *head)
{
    int open = 0;
    int close = 0;
    ast_t *(*ptr)(ast_t *, bool *) = NULL;
    bool post = false;

    if (!check_par(command_tree, &open, &close)) {
        free_ast(command_tree);
        head->lr = 1;
        return NULL;
    }
    if (command_tree->data == par_open || command_tree->data == par_close) {
        ptr = command_tree->data;
        command_tree = ptr(command_tree, &post);
    }
    if (!check_tree(command_tree, 0)) {
        free_ast(command_tree);
        head->lr = 1;
        return NULL;
    }
    return command_tree;
}

int separator_handler(char *command_line, head_t *head)
{
    ast_t *command_tree = NULL;
    int r = 0;
    if (!command_line) return 84;
    if (only_st(command_line)) return head->lr;
    command_line = pre_parsing(command_line, head);
    if (!command_line) return head->lr;
    head->stdin_copy = dup(0);
    head->stdout_copy = dup(1);
    command_tree = build_ast(command_line, 0);
    if (!command_tree) {
        head->keep = false;
        return 84;
    }
    command_tree = post_parsing(command_tree, head);
    if (!command_tree) return head->lr;
    r = execute(command_tree, 0, 1, head);
    free_ast(command_tree);
    dup2(head->stdin_copy, 0);
    dup2(head->stdout_copy, 1);
    return r;
}
