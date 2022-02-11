/*
** EPITECH PROJECT, 2022
** malloc
** File description:
** tests_my_memory
*/

#include "my_tests.h"

Test(malloc, my_malloc_my_free_test)
{
    void *handle = dlopen("./libmy_malloc.so", RTLD_LAZY);
    void *(*my_malloc)(size_t);
    void *(*my_free)(void *);
    void *ptr;

    cr_assert_not_null(handle);
    cr_assert_not_null(my_malloc = dlsym(handle, "__malloc__"));
    cr_assert_not_null(my_free = dlsym(handle, "__free__"));
    cr_log_warn("500 mallocs of 200000 bytes\n");
    for (int i = 0; i < 500; i++) {
        ptr = my_malloc(200000);
        memset(ptr, 0, 200000);
    }
    cr_assert_null(dlclose(handle));
}

int t_realloc(void *(*my_malloc)(size_t), void *(*my_realloc)(void *, size_t))
{
    char *string;
    char *string2;
    int a = 0;

    string = my_malloc(100);
    memset(string, 'a', 100);
    string[99] = '\0';
    string2 = my_realloc(string, 1000);
    if (strcmp(string, string2) != 0)
        a = 1;
    memset(string2, 0, 1000);
    return (a);
}

Test(realloc, my_realloc_test)
{
    void *handle = dlopen("./libmy_malloc.so", RTLD_LAZY);
    void *(*my_realloc)(void *, size_t);
    void *(*my_malloc)(size_t);
    int a = 0;

    cr_assert_not_null(handle);
    cr_assert_not_null(my_malloc = dlsym(handle, "__malloc__"));
    cr_assert_not_null(my_realloc = dlsym(handle, "__realloc__"));
    cr_log_warn("500 realloc of 1000 bytes\n");
    for (int i = 0; i < 1; i++)
        a += t_realloc(my_malloc, my_realloc);
    cr_assert_eq(a, 0);
    dlclose(handle);
}

Test(realloc, my_realloc_test_bigger)
{
    void *handle = dlopen("./libmy_malloc.so", RTLD_LAZY);
    void *(*my_reallocarray)(void *, size_t, size_t);
    void *(*my_free)(void *);
    void *ptr = NULL;

    cr_assert_not_null(handle);
    cr_assert_not_null(my_reallocarray = dlsym(handle, "__reallocarray__"));
    cr_assert_not_null(my_free = dlsym(handle, "__free__"));
    cr_log_warn("realloc bigger size\n");
    ptr = my_reallocarray((void *)1, 2000, 1);
    ptr = my_reallocarray(NULL, 2000, 1);
    memset(ptr, 0, 2000);
    ptr = my_reallocarray(ptr, 1000, 1);
    memset(ptr, 0, 1000);
    ptr = my_reallocarray(ptr, 10000, 1);
    memset(ptr, 0, 10000);
    ptr = my_reallocarray(ptr, 0, 0);
    cr_assert_null(dlclose(handle));
}

Test(calloc, my_calloc_test)
{
    void *handle = dlopen("./libmy_malloc.so", RTLD_LAZY);
    void *(*my_calloc)(size_t, size_t);
    void *(*my_free)(void *);
    void *ptr = NULL;

    cr_assert_not_null(handle);
    cr_assert_not_null(my_calloc = dlsym(handle, "__calloc__"));
    cr_assert_not_null(my_free = dlsym(handle, "__free__"));
    cr_log_warn("calloc of 1000 bytes\n");
    ptr = my_calloc(1, 1000);
    memset(ptr, 0, 1000);
    cr_assert_null(dlclose(handle));
}