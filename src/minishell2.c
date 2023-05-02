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
#include "mysh.h"
#include "ast.h"

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
    if (line[i] == '\0')
        return true;
    return false;
}

int separator_handler(char *command_line, head_t *head)
{
    ast_t *command_tree = NULL;
    int r = 0;

    if (only_st(command_line)) return 0;
    if (!command_line) return 84;
    command_line = change_command(command_line, head);
    head->stdin_copy = dup(0);
    head->stdout_copy = dup(1);
    command_tree = build_ast(command_line, 0);
    if (!command_tree) {
        head->keep = false;
        return 84;
    }
    if (!check_tree(command_tree, 0)) return 1;
    r = execute(command_tree, 0, 1, head);
    free_ast(command_tree);
    dup2(head->stdin_copy, 0);
    dup2(head->stdout_copy, 1);
    return r;
}
