/*
** EPITECH PROJECT, 2023
** minishell2 [WSL: fedora]
** File description:
** my_printf
*/

#include <stdarg.h>
#include "mystr.h"

static void apply_flags(int fd, char const *format, va_list ap)
{
    if (*format == 's')
        my_fputstr(fd, va_arg(ap, char *));
    if (*format == 'c')
        my_fputchar(fd, va_arg(ap, int));
    if (*format == 'd')
        my_fputnbr(fd, va_arg(ap, int));
}

void my_fprintf(int fd, char const *format, ...)
{
    va_list ap;

    va_start(ap, format);
    while (*format != '\0') {
        if (*format == '%') {
            format++;
            apply_flags(fd, format, ap);
        } else
            my_fputchar(fd, *format);
        format++;
    }
    va_end(ap);
}
