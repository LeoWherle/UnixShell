/*
** EPITECH PROJECT, 2023
** 42sh [WSL: fedora]
** File description:
** prompt
*/

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "mysh.h"
#include "ansi_colors.h"

static int print_host(void)
{
    char host_name[MAX_BUFFER_SIZE];
    int length = 0;

    memset(host_name, 0, MAX_BUFFER_SIZE - 1);
    gethostname(host_name, MAX_BUFFER_SIZE);
    printf(BOLD RED"@"GREEN"%s:"RESET, host_name);
    length = strlen(host_name) + 2;
    return length;
}

static int print_dir(void)
{
    char *cwd = NULL;
    char *dir = NULL;
    char *token = NULL;
    int length = 0;

    cwd = getcwd(cwd, 0);
    token = strtok(cwd, "/");
    if (token == NULL)
        dir = "/";
    while (token != NULL) {
        dir = token;
        token = strtok(NULL, "/");
    }
    printf(BOLD MAGENTA"%s"WHITE"]"RESET, dir);
    length = strlen(dir) + 1;
    free(cwd);
    return length;
}

static char *get_current_branch(void)
{
    char buffer[MAX_BUFFER_SIZE];
    char command[MAX_BUFFER_SIZE] = BRANCH_COMMAND;
    char *branch_name = NULL;
    FILE* fp = NULL;

    if ((fp = popen(command, "r")) == NULL) {
        return NULL;
    }
    if (fgets(buffer, MAX_BUFFER_SIZE, fp) == NULL) {
        pclose(fp);
        return NULL;
    }
    buffer[strcspn(buffer, "\n")] = '\0';
    pclose(fp);
    branch_name = strdup(buffer);
    return branch_name;
}

static int print_branch(void)
{
    char *branch = NULL;
    int length = 0;

    branch = get_current_branch();
    if (branch != NULL) {
        printf(BOLD YELLOW"[%s]"RESET, branch);
        length = strlen(branch) + 2;
        free(branch);
    }
    return length;
}

/**
 * @brief Print the shell prompt with the current user, host, directory and
 * current branch if there is one.
 *
 * @return the length of the printed prompt
 */
int print_shell(void)
{
    char *user = NULL;
    int length = 0;

    user = getenv("USER");
    length += print_host();
    length += print_dir();
    length += print_branch();
    printf(BOLD RED"$ "RESET);
    length += 2;
    ASSERT_PTR(user, length);
    printf(BOLD WHITE"["CYAN"%s"RESET, user);
    length += 1 + strlen(user);
    return length;
}
