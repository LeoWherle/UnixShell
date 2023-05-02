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

static void print_host(void)
{
    char host_name[MAX_BUFFER_SIZE];

    gethostname(host_name, MAX_BUFFER_SIZE);
    printf(BOLD RED"@"GREEN"%s:"RESET, host_name);
}

static void print_dir(void)
{
    char *cwd = NULL;
    char *dir = NULL;
    char *token = NULL;

    cwd = getcwd(cwd, 0);
    token = strtok(cwd, "/");
    if (token == NULL)
        dir = "/";
    while (token != NULL) {
        dir = token;
        token = strtok(NULL, "/");
    }
    printf(BOLD MAGENTA"%s"WHITE"]"RESET, dir);
    free(cwd);
}

static char *get_current_branch(void)
{
    char buffer[MAX_BUFFER_SIZE];
    char command[MAX_BUFFER_SIZE] = BRANCH_COMMAND;
    char *branch_name = NULL;
    FILE* fp;

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

static void print_branch(void)
{
    char *branch = get_current_branch();

    if (branch != NULL) {
        printf(BOLD YELLOW"[%s]"RESET, branch);
        free(branch);
    }
}

void print_shell(void)
{
    char *user = NULL;

    DEBUG_ERROR_CHECK(user);
    user = getenv("USER");
    printf(BOLD WHITE"["CYAN"%s"RESET, user);
    print_host();
    print_dir();
    print_branch();
    printf(BOLD RED"$ "RESET);
}
