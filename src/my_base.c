/*
** EPITECH PROJECT, 2022
** malloc
** File description:
** my_base
*/

#include "my_memory.h"

size_t get_page_size(size_t size)
{
    int ps = getpagesize();
    size_t pages = size / ps ? (size / ps) + (size % ps) : 2;

    return ps * (pages + (pages % 2 != 0));
}

void **base(void)
{
    static void *base_block = NULL;
    return &base_block;
}

void *get_ptr(void *ptr)
{
    if (*base() && ptr < sbrk(0) && ptr == (get_block(ptr))->ptr)
        return get_block(ptr);
    return NULL;
}
