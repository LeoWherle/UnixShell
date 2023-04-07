/*
** EPITECH PROJECT, 2023
** B-MUL-200-TLS-2-1-mypaint-theodore.magna [WSL: fedora]
** File description:
** errorhandling
*/

#include <stddef.h>

#ifndef ERRORHANDLING_H_
    #define ERRORHANDLING_H_
    #define ERROR 84
    #define SUCCESS 0
    #define UNUSED __attribute__((unused))
    #define DEPRECATED __attribute__((deprecated))
    #define LIKELY(x)       __builtin_expect((x),1)
    #define UNLIKELY(x)     __builtin_expect((x),0)
    #define ASSERT_MALLOC(ptr, retrn) if (UNLIKELY(ptr == NULL)) return retrn;
    #define ASSERT_PTR(ptr, retrn) if (ptr == NULL) return retrn;

#endif /* !ERRORHANDLING_H_ */
