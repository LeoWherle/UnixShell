/*
** EPITECH PROJECT, 2023
** 42sh [WSL: fedora]
** File description:
** basic_keys
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "errorh.h"
#include "prompt.h"
#include "mystr.h"
#include "auto_complete.h"

int enter_key(UNUSED textfield_t *field, UNUSED head_t *head)
{
    if (isatty(STDIN_FILENO)) {
        putchar('\n');
    }
    return 1;
}

static char **init_file_list(char **file_list, textfield_t *field)
{
    int nb = 0;

    nb = get_file_nb("./");
    if (nb == -1)
        return NULL;
    if (!is_in(' ', field->buffer) && field->cursor_pos != 0)
        nb += get_file_nb("/usr/bin/");
    file_list = malloc(sizeof(char *) * (nb + 1));
    ASSERT_MALLOC(file_list, NULL);
    file_list[0] = NULL;
    file_list = get_file_list(file_list, "./");
    ASSERT_MALLOC(file_list, NULL);
    if (!is_in(' ', field->buffer) && field->cursor_pos != 0) {
        file_list = get_file_list(file_list, "/usr/bin/");
        ASSERT_MALLOC(file_list, NULL);
    }
    sort_files(file_list);
    return file_list;
}

int tab_key(textfield_t *field, UNUSED head_t *head)
{
    char **file_list = NULL;
    char *command = NULL; char *tmp = NULL;

    file_list = init_file_list(file_list, field);
    ASSERT_PTR(file_list, 0);
    command = get_command(field->buffer);
    file_list = get_corresponding_files(file_list, command);
    ASSERT_PTR(file_list, 0);
    ASSERT_PTR(file_list[0], 0);
    if (matrix_len(file_list) > 1) {
        print_fake_ls(file_list);
        tmp = get_best_match(file_list);
    } else
        tmp = file_list[0];
    memmove(command, tmp, strlen(tmp));
    field->bf_size = strlen(field->buffer) + strlen(tmp) - strlen(command);
    field->cursor_pos = field->bf_size;
    if (tmp != file_list[0]) free(tmp);
    free_matrix(file_list);
    return 0;
}

int backspace_key(textfield_t *field, UNUSED head_t *head)
{
    if (field->cursor_pos > 0) {
        memmove(field->buffer + field->cursor_pos - 1,
            field->buffer + field->cursor_pos,
            field->bf_size - field->cursor_pos + 1);
        (field->cursor_pos)--;
        field->bf_size--;
    }
    return 0;
}
