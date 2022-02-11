/*
** EPITECH PROJECT, 2022
** malloc
** File description:
** my_alloc
*/

#include "my_memory.h"

void *calloc(size_t number, size_t size)
{
    size_t *new = malloc(number * size);

    if (new) {
        for (size_t i = 0; i < number; i++) {
            new[i] = 0;
        }
    }
    return new;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
    return realloc(ptr, nmemb * size);
}

static void *realloc_resize(void *ptr, size_t size_align, t_block block)
{
    t_block new_block;
    void *new_ptr;

    if (block->next && block->next->free &&
        (block->size + BLOCK_SIZE + block->next->size) >= size_align) {
        fusion(block);
        if (block->size - size_align >= (BLOCK_SIZE + 4))
            split_block(block, size_align);
    } else {
        new_ptr = malloc(size_align);
        if (!new_ptr)
            return NULL;
        new_block = get_block(new_ptr);
        copy_block(block, new_block);
        free(ptr);
        return new_ptr;
    }
    return ptr;
}

void *realloc(void *ptr, size_t size)
{
    t_block block = get_ptr(ptr);
    size_t size_align = ALIGN4(size);

    if (ptr == NULL)
        return malloc(size);
    if (block) {
        if (block->size >= size_align) {
            if (block->size - size_align >= (BLOCK_SIZE + 4))
                split_block(block, size_align);
        } else
            return realloc_resize(ptr, size_align, block);
        return ptr;
    }
    return NULL;
}
