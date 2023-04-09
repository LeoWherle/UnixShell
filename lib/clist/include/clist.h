/*
** EPITECH PROJECT, 2023
** Personal_Clib [WSL: fedora]
** File description:
** chained_list
*/

#ifndef CLIST_H_
    #define CLIST_H_
    #ifndef ERRORHANDLING_H_
        #define ERROR 84
        #define SUCCESS 0
        #define UNUSED __attribute__((unused))
        #define DEPRECATED __attribute__((deprecated))
        #define LIKELY(x)       __builtin_expect((x),1)
        #define UNLIKELY(x)     __builtin_expect((x),0)
        #define ASSERT_MALLOC(ptr, ret) if (UNLIKELY(ptr == NULL)) return ret;
        #define ASSERT_PTR(ptr, retrn) if (ptr == NULL) return retrn;
    #endif /* !ERRORHANDLING_H_ */

    #ifndef STRING_LIST_H_
        #define STRING_LIST_H_
        void *string_dup(void *str);
        void string_free(void *data);
    #endif /* !STRING_LIST_H_ */

    typedef struct node_s node_t;
    typedef struct list_s list_t;
    typedef struct list_interface list_interface_t;
    typedef void * any_t;

    typedef void (*fun_free_data)(void *);
    typedef void (*fun_foreach_wargs)(any_t data, void *arg, void *arg2);
    typedef void (*fun_foreach)(any_t data);
    typedef void (*fun_print)(any_t data);

    typedef struct node_s {
        any_t data;
        node_t *next;
        node_t *prev;
    } node_t;

    /**
     * @brief list structure
     *
     * @param head the first node of the list
     * @param tail the last node of the list
     * @param size the size of the list
     * @param interface methods of the list (shared between all lists)
     */
    typedef struct list_s {
        node_t *head;
        node_t *tail;
        int size;
        list_interface_t *interface;
    } list_t;

    typedef struct list_interface {
        int (*append)(list_t *list, any_t data);
        int (*insert)(list_t *list, any_t data);
        any_t (*popf)(list_t *list);
        any_t (*pop)(list_t *list, any_t data);
        void (*append_list)(list_t *list_dest, list_t *list_src);
        void (*insert_list)(list_t *list_dest, list_t *list_src);
        void (*print)(list_t *list, fun_print, const char *sep);
        node_t *(*find)(list_t *list, const any_t data);
        void (*destroy)(list_t *list, fun_free_data);
    } list_interface_t;

    node_t *node_init(any_t data);
    list_t *list_init(void);

    int node_append(list_t *list, any_t data);
    int node_insert(list_t *list, any_t data);

    any_t node_popf(list_t *list);
    any_t node_pop(list_t *list, any_t data);

    void list_append(list_t *list_dest, list_t *list_src);
    void list_insert(list_t *list_dest, list_t *list_src);

    void list_foreach_wargs(list_t *list, fun_foreach_wargs,
                            void *arg1, void *arg2);
    void list_foreach(list_t *list, fun_foreach);
    node_t *node_find(list_t *list, const any_t data);

    int node_delete(list_t *list, any_t data, fun_free_data);
    int node_destroy(list_t *list, fun_free_data);
    void list_destroy(list_t *list, fun_free_data);

    void list_print(list_t *list, fun_print, const char *sep);
    any_t *array_build(list_t *list);
    list_t *list_build(char **array);

    list_t *list_dup(list_t *list, any_t (*dup_data)(any_t data));

#endif /* !CLIST_H_ */
