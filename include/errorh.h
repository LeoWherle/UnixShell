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
    #define WUR __attribute__((warn_unused_result))
    #define NONULL __attribute__((nonnull(arg1, arg2, ...)))
    #define LIKELY(x)       __builtin_expect((x),1)
    #define UNLIKELY(x)     __builtin_expect((x),0)
    #define ASSERT_MALLOC(ptr, retrn) if (UNLIKELY(ptr == NULL)) return retrn;
    #define ASSERT_PTR(ptr, retrn) if (ptr == NULL) return retrn;

    #ifdef DEBUG
        #define REDDB "\033[1;31m"
        #define MGTDB "\033[1;35m"
        #define RST "\033[0m"
        #define PRINTARGS(str) __FILE__, __LINE__, __func__, str
        #define FMT MGTDB"Error: "RST"%s:%d: %s: assertion '%s' failed.\n"
        #define DEBUG_PRINT(str) fprintf(stderr, FMT, PRINTARGS(str))
        #define DEBUG_ERROR_CHECK(expr) if (!(expr)) { DEBUG_PRINT(#expr); }
    #else
        #define DEBUG_ERROR_CHECK(expr) do { } while (0)
        #define DEBUG_PRINT(str) do { } while (0)
    #endif

#endif /* !ERRORHANDLING_H_ */
